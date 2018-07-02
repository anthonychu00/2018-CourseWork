#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct player{
    char *name;
    SQUARE currentSpace;
    char * (* toString)(void* S);
}player_t;

typedef player_t * PLAYER;


PLAYER newPlayer(char *name, void *currentSpace, char * (* toString)(void* S));

void printItS(void * S);  

char * toString (void* S);
