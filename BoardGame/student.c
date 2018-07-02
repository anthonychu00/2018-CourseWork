#include "student.h"


STUDENT newStudent(int id, char *name, char * (* toString)(void* S)){
  STUDENT s;
  s = (STUDENT) malloc(sizeof(student_t));
  s->id=id;
  s->name=(char*) malloc(sizeof(char)*20);
  strcpy(s->name,name);
    s->toString = toString;
  return s;

}
void printIt(void * S){
  STUDENT s;
  s = (STUDENT) S;
  puts(s->toString(s));
}

int  compare(void * A, void * B){
  STUDENT s1;
  char * item;
  item  = (char *) A;
  s1 = (STUDENT) B;
  //printf("%s",item);
  //printf("%s",s1->name);
  //printf("%d",strcmp(item,s1->name));
  strncmp(item,s1->name, strlen(item)-1);
  return (strcmp(item,s1->name));
}

char * toString (void* S){
  char * buffer;
  STUDENT s;
  s = (STUDENT) S;
    buffer = (char *) malloc(sizeof(char)*200);
    sprintf(buffer,"ID: %d NAME: %s",s->id, s->name);
  return buffer;

}
