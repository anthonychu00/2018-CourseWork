#include "square.h"


SQUARE newSquare(char *color, char *special, int x, char * (* toStringS)(void* S)){
  SQUARE s;
  s = (SQUARE) malloc(sizeof(square_t));
  s->color=(char*) malloc(sizeof(char)*20);
  strcpy(s->color,color);
  s->special=(char*) malloc(sizeof(char)*20);
  strcpy(s->special,special);
  s->x=x;
  s->toStringS = toStringS;
  return s;

}
void printIt(void * S){
  SQUARE s;
  s = (SQUARE) S;
  puts(s->toStringS(s));
}

int  compare(void * A, void * B){//might need compare for color/x
  SQUARE s1;
  char * item;
  item  = (char *) A;
  s1 = (SQUARE) B;
  //printf("%s",item);
  //printf("%s",s1->name);
  //printf("%d",strcmp(item,s1->name));
  return (strncmp(item,s1->color, strlen(item)-1));
}

char * toStringS (void* S){
  char * buffer;
  SQUARE s;
  s = (SQUARE) S;
    buffer = (char *) malloc(sizeof(char)*200);
    sprintf(buffer,"COLOR: %s SPECIAL: %s X: %d",s->color, s->special, s->x);
  return buffer;

}
