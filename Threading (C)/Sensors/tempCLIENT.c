#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "sensors.h"
#include "genericDouble.h"
#define NUM_OF_CYCLES 10

pthread_mutex_t lock;
pthread_cond_t complete;
LIST glList;//global linkedlist to add stuff to
int finishedSensors;
int numSensors;
sensor_t* sensorHead;

int main(){
  srand(time(NULL));
  finishedSensors=0;
  glList=NULL;
  sensorHead=NULL;
  LIST l;
  sensor_t* s;
  char* howMany = (char*)malloc(sizeof(char));
  pthread_t id;

  printf("How many sensors?");
  scanf("%s",howMany);
  numSensors=atoi(howMany);

  pthread_mutex_init(&lock, NULL);
  for(int i=0;i<numSensors;i++){
    s=makeNewSensor(i);
    sensorHead=addToRear(sensorHead,s);
  }
  for(s=sensorHead;s!=NULL;s=s->next){
    pthread_cond_init(&complete, NULL);
    pthread_create(&(s->tid),NULL,(void*)sensors,s->threadNum);
  }

  for(s=sensorHead;s!=NULL;s=s->next)
    {
      pthread_join((s->tid),NULL);
    }
    sensor_t* deleter=sensorHead;
    while(deleter){
      sensor_t* del =deleter;
      deleter=deleter->next;
      free(del);//frees sensors just in case
    }
    free(glList);
    free(howMany);
    exit(0);
}
void sensors(int *t) {
  int sensorNum, cycles = 1;
  sensorNum = *t + 1;
  while (cycles <= NUM_OF_CYCLES) {
    addToList(sensorNum, cycles);
    lastSensorInCycle(sensorNum);
    waitForCycleToFinish(sensorNum,cycles);
    printf("Cycles is now %d for thread %d \n",cycles,sensorNum);
    cycles++;
  }
  printf("all cycles completed %d is done\n", sensorNum);
  pthread_exit(NULL);
}

sensor_t *makeNewSensor(int threadN){
  sensor_t*s;
  s=(sensor_t*)malloc(sizeof(sensor_t));
  s->threadNum=(int*)malloc(sizeof(int));
  *(s->threadNum)=threadN;
  s->temp=(int*)malloc(sizeof(int));
  *(s->temp)=1;
  s->last=(int*)malloc(sizeof(int));
  *(s->last)=1;//1 is false, 2 is true to get around 0 being equal to null
  s->wasWaiting=(int*)malloc(sizeof(int));
  *(s->wasWaiting)=1;
  s->next=NULL;
  return s;
}
sensor_t *addToRear(sensor_t *head, sensor_t *n) {

sensor_t* s;
if(head==NULL)
  return n;
s=head;
while(s->next!=NULL){
  s=s->next;
}
s->next=n;
return head;
}

void addToList(int t, int cycles) {
  LIST l;
  int rando=(1 + rand() % 100);
  //printf("Value of rando is %d \n", rando);
  sensor_t *s;
  LIST p;
  pthread_mutex_lock(&lock);
  s=findSensor(t);
  *(s->temp)=rando;
  p=makeNewListNode(s->temp);
  glList=insert_rear(glList,p);
  pthread_mutex_unlock(&lock);
}

void waitForCycleToFinish(int t, int cycles) {
  int passing=0;
  int average=0;
  sensor_t *s;
  pthread_mutex_lock(&lock);
  s=findSensor(t);
  while(finishedSensors!=0&&*(s->last)!=2&&*(s->wasWaiting)!=2)//blocks all sensors but the last
  {
    //printf("Thread: %d is waiting\n",*(s->threadNum));
    *(s->wasWaiting)=2;
    pthread_cond_wait(&complete,&lock);
    //printf("Thread: %d woke up\n",*(s->threadNum));
  }

  if(*(s->last)==2){//special instructions for last sensor
    LIST y=glList;
    int* x;
    while(y!=NULL)//prints out completed list
    {
      x=(int*)(y->item);
      average+=*x;
      printf("%d\n",*x);
      y=y->next;
    }
    printf("The average is %d\n",average/numSensors);
    //printf("Reseting list");
    glList=NULL;
    finishedSensors=0;
    *(s->last)=1;
    //printf("Thread: %d is waking everyone up\n",*(s->threadNum));
    while(passing<numSensors)
    {
      pthread_cond_signal(&complete);
      passing++;
    }
  }

  if(*(s->wasWaiting)==2)
    *(s->wasWaiting)=1;

  pthread_mutex_unlock(&lock);
  //printf("We're free\n");
}

void lastSensorInCycle(int t) {
  sensor_t *s;
  pthread_mutex_lock(&lock);
  s=findSensor(t);
  finishedSensors++;
  if(finishedSensors==numSensors)//assigns a thread the title of last sensor
  {
    //printf("Thread: %d is the last thread\n",*(s->threadNum));
    *(s->last)=2;
  }

  pthread_mutex_unlock(&lock);
}

sensor_t* findSensor(int t)//gets the sensor of the current sensor num
{
  sensor_t *s;
  s=sensorHead;
  for(int i=1;i<=numSensors;i++)
  {
    if((*(s->threadNum)+1)==t)
      return s;
    s=s->next;
  }
  printf("Error");
  exit(0);
}
