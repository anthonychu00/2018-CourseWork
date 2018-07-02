#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct square{
    char *color;
    char *special;
    int x;
    char * (* toStringS)(void* S);
}square_t;

typedef square_t * SQUARE;


SQUARE newSquare(char *color, char *special, int x, char * (* toStringS)(void* S));

void printIt(void * S);  //for all stocks
int  compare(void * A, void * B); //for all stocks

char * toStringS (void* S);
