#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct passenger{
  pthread_t tid;//id is not technically an int
  int* threadNum;//actual "number" of id
  struct passenger *next;
}passenger_t;

typedef passenger_t *PASSEN;
PASSEN makeNewPassenger();
PASSEN addToRear(PASSEN head, PASSEN n);
void takeRide(int t);
void passengers(int *t);
PASSEN findPassenger(int t);
