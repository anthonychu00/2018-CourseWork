#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student{
    int id;
    char *name;
    char * (* toString)(void* S);
}student_t;

typedef student_t * STUDENT;


STUDENT newStudent(int id, char *name, char * (* toString)(void* S));

void printIt(void * S);  //for all stocks
int  compare(void * A, void * B); //for all stocks

char * toString (void* S);
