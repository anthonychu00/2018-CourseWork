#include "square.h"
#include "player.h"

PLAYER newPlayer(char *name, void* currentSpace, char * (* toString)(void* S)){
  PLAYER s;
  SQUARE sq =(SQUARE)currentSpace;//make sure the void* is passed in as a square, not list
  s = (PLAYER) malloc(sizeof(player_t));
  s->name=(char*) malloc(sizeof(char)*20);
  strcpy(s->name,name);
  s->currentSpace=sq;
  s->toString = toString;
  return s;

}
void printItS(void * S){
  PLAYER s;
  s = (PLAYER) S;
  puts(s->toString(s));
}


char * toString (void* S){
  char * buffer;
  PLAYER s;
  s = (PLAYER) S;
    buffer = (char *) malloc(sizeof(char)*200);
    sprintf(buffer,"PLAYERNAME: %s CURRENT SPACE IS %s ",s->name, toStringS(s->currentSpace));
  return buffer;

}
