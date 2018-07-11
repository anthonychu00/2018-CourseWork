#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "car.h"
#include "passenger.h"

int onBoard;//number of passengers in cars
int capacity;//capacity of the car to be determined by users
int numPassengers;//number of passengers to be determined by users
int openForService=0, inCar=0, lastCar=0, loading=0;
PASSEN passengerList;

pthread_mutex_t lock;//remember to init both the mutex and cond
pthread_cond_t waiting;
pthread_cond_t stayInCar;
pthread_cond_t canIGo;
pthread_cond_t emptying;
pthread_cond_t loader;


int main(int argc, char *argv[]){
  if(argc<3 ||argc >4)
  {
    printf("Incorrect number of arguments\n");
    exit(0);
  }
  numPassengers=atoi(argv[1]);//first argument is passengers
  capacity=atoi(argv[2]);//second argument is capacity
  onBoard=0;
  CAR c;
  PASSEN p;
  pthread_cond_init(&waiting, NULL);
  pthread_cond_init(&stayInCar, NULL);
  pthread_cond_init(&canIGo, NULL);
  pthread_cond_init(&loader, NULL);
  pthread_cond_init(&emptying, NULL);
  pthread_mutex_init(&lock, NULL);

  for(int i=0;i<numPassengers;i++){//creates all passengers
    p=makeNewPassenger(i);
    passengerList=addToRear(passengerList,p);
  }
  c=makeNewCar(1,capacity);//creates the car

  for(p=passengerList;p!=NULL;p=p->next){//calls passengers
    pthread_create(&(p->tid),NULL,(void*)passengers,p->threadNum);
  }
  pthread_create(&(c->tid),NULL,(void*)cars,c->threadNum);//calls car

  pthread_join((c->tid),NULL);
  free(c);//frees car
  PASSEN deleter=passengerList;
  while(deleter){
    PASSEN del =deleter;
    deleter=deleter->next;
    free(del);//frees passengers
  }
  exit(0);
}

void cars(int *t){//start function for the car
  int numberServed=0;
  pthread_mutex_lock(&lock);
  while(numberServed<numPassengers)
  {
    openForService=1;
    printf("Loading passengers\n");
    loadCustomers();
    if(capacity+numberServed>=numPassengers){//checks if the remaining customers are the last car
      lastCar=1;
      while(onBoard+numberServed!=numPassengers)
        pthread_cond_wait(&canIGo,&lock);
      printf("No others waiting\n");
    }
    else{//else continue as normal
      while(onBoard<capacity){
        pthread_cond_wait(&canIGo,&lock);
        printf("We are full\n");
      }
    }
    openForService=0;
    printf("Let's go for a ride\n");
    printf("....\n");
    sleep(1);
    printf("Done\n");
    inCar=1;
    numberServed=unloadCustomers(numberServed);//keeps track of people already taken the ride
    while(onBoard!=0)
      pthread_cond_wait(&emptying,&lock);
    inCar=0;

    //printf("Number served is now %d\n",numberServed);

  }
  pthread_mutex_unlock(&lock);
  printf("Thanks for visiting\n");
  pthread_exit(NULL);
}

void takeRide(int t){
  PASSEN p;
  p=findPassenger(t);
  pthread_mutex_lock(&lock);//passenger begins process of getting into car
  while(openForService==0||onBoard==capacity){//passenger waits here until the car is open(not riding or unloading people)
    pthread_cond_wait(&waiting,&lock);
    printf("Passenger %d is boarding\n",*(p->threadNum));
    loading=1;
  }
  onBoard++;
  printf("On board: %d\n",onBoard);
  if(onBoard==capacity||lastCar==1)//checks if car is full or if the last person is in car
    pthread_cond_signal(&canIGo);//turns service back to 0
  loading=0;
  pthread_cond_signal(&loader);//tells loader to get next customer on

  while(inCar==0)
    pthread_cond_wait(&stayInCar,&lock);//people wait in the car
  printf("Passenger %d is unboarding\n",*(p->threadNum));
  onBoard--;
  if(onBoard==0){//signals the car its empty and that it can take more passengers
    printf("Empty now\n");
    pthread_cond_signal(&emptying);
  }
  pthread_mutex_unlock(&lock);
}

void loadCustomers(){
  for(int i=0;i<capacity;i++)
  {
    pthread_cond_signal(&waiting);
    while(loading=0){
      pthread_cond_wait(&loader,&lock);
    }
  }
}

int unloadCustomers(int t){
  for(int i=0;i<onBoard;i++)
  {
    t++;
    pthread_cond_signal(&stayInCar);//relasing threads from car
  }
  return t;
}

void passengers(int *t){
  int passNum = *t + 1;
  takeRide(passNum);
  pthread_exit(NULL);
}
//-----------------------------------------------------------------
CAR makeNewCar(int carNum, int capacity){
    CAR c;
    c=(CAR)malloc(sizeof(CAR));
    c->threadNum=(int*)malloc(sizeof(int));
    *(c->threadNum)=carNum;
    c->capacity=capacity;
    return c;
}

PASSEN makeNewPassenger(int threadNum){
    PASSEN p;
    p=(PASSEN)malloc(sizeof(PASSEN));
    p->threadNum=(int*)malloc(sizeof(int));
    *(p->threadNum)=threadNum;
    p->next=NULL;
    return p;
}

PASSEN addToRear(PASSEN head, PASSEN n) {
  PASSEN s;
  if(head==NULL)
    return n;
  s=head;
  while(s->next!=NULL){
    s=s->next;
  }
  s->next=n;
  return head;
}

PASSEN findPassenger(int t)
{
  PASSEN s;
  s=passengerList;
  for(int i=1;i<=numPassengers;i++)
  {
    if((*(s->threadNum)+1)==t)
      return s;
    s=s->next;
  }
  printf("Error");
  exit(0);
}
