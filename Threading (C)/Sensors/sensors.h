#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct sensor{
  pthread_t tid;//id is not technically an int
  int* threadNum;//actual "number" of id
  int* temp;
  int* last;
  int* wasWaiting;
  struct sensor *next;
}sensor_t;

sensor_t * makeNewSensor(int threadN);
void sensors(int *t);
sensor_t *addToRear(sensor_t *head, sensor_t *n);
void addToList(int t, int cycles);
sensor_t *makeNewSensor(int threadN);
void waitForCycleToFinish(int t, int cycles);
void lastSensorInCycle(int t);
sensor_t* findSensor(int t);
