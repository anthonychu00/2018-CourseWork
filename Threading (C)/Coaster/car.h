#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct car{
  pthread_t tid;//id is not technically an int
  int* threadNum;//actual "number" of id
  int capacity;
}car_t;

typedef car_t *CAR;

CAR makeNewCar(int carNum, int capacity);
void loadCustomers();
int unloadCustomers(int t);
void cars(int *t);
