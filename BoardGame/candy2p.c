#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "genericDouble.h"
#include "square.h"
#include "player.h"

//some prototypes for this project
//int menu();
SQUARE makeSquareNode(char buffer[]);
LIST readFile();
char* playGame(LIST head, LIST end, LIST playerHead);
LIST moveForward(LIST current, char *color, int *breaker);
char* processColor(int i);
int randomNumber(int upperBound);

int main(int argc, char *argv[]){
  srand(time(NULL));
  LIST head, end, playerHead;//*node_t
  PLAYER p1,p2;
  SQUARE placeholder;//when players are not yet on a board, can't be null
  char* p1Name, *p2Name, *gameWin;//names for the two players
  int sum=0;
  head=NULL;
  end=NULL;

  placeholder=newSquare("NOT ON A SPACE","NOT ON A SPACE",0,toStringS);
  p1Name = (char*) malloc(sizeof(char)*20);
  p2Name = (char*) malloc(sizeof(char)*20);
  printf("What is player 1's name?");
  //scanf("%s",p1Name);
  fgets(p1Name,20,stdin);
  printf("What is player 2's name?");
  //scanf("%s",p2Name);
  fgets(p2Name,20,stdin);

  p1 =newPlayer(p1Name,placeholder,toString);
  p2 =newPlayer(p2Name,placeholder,toString);
  playerHead=makeNewListNode(p1);
  playerHead=insert_rear(playerHead, makeNewListNode(p2));

  printf("The players are:\n");
  displayForward(playerHead, printItS);

  head=readFile();
  if(head!=NULL)
    end=findEnd(head);

  printf("This is the board\n");
  displayForward(head,printIt);
  gameWin = playGame(head,end, playerHead);
  printf("%s won\n",gameWin);
  printf("Done\n");
  LIST deleter =head;//frees everything
  while(deleter){
    LIST del =deleter;
    deleter=deleter->next;
    free(del);
  }
 deleter =playerHead;
  while(deleter){
    LIST del =deleter;
    deleter=deleter->next;
    free(del);
  }
  exit(0);
}

LIST readFile(){
  FILE *inf = fopen("board.txt", "r"); //opens a file for READING
  char buffer[80];
  SQUARE S;
  LIST head, l;
  int count = 0, answer;
  head = NULL;

    if (inf == NULL){
        puts("no file you idiot");
        exit(1);
    }

  while (1) {
      fgets(buffer, 80, inf); //reads in at most 80 char from a line
      if (feof(inf))
         break;

          //if so, break out of while and continue with your main
    S = makeSquareNode(buffer);
       count++;
    l = makeNewListNode(S);
    head =  insert_rear(head,l);//now you need to insert the stock into a node of the generic link list
  }

  fclose(inf);  //Closes a file.
  printf("%d new records were read\n", count);
  return head;
  //Hopefully, at this point, the data is nicely stored in the generic link list
}

char* playGame(LIST head, LIST end, LIST playerHead)
{
  if (head==NULL)
    return " ";
  if (playerHead==NULL)
  {
    printf("No one is playing");
    return " ";
  }
  char *winner;
  winner =(char*) malloc(sizeof(char)*20);
  int breakPoint=0;//detects for infinite loops
  LIST temp;
  LIST otherCurrent=head;
  LIST current=head;
  LIST starter=playerHead;
  PLAYER currentPlayer;
  SQUARE currentItem= (SQUARE)(current->item);
  while(starter!=NULL)//puts all players on the start of the board
  {
    currentPlayer=(PLAYER)(starter->item);
    currentPlayer->currentSpace=currentItem;
    starter=starter->next;
  }//good they're on the board at least

  printf("The players are:\n");
  displayForward(playerHead, printItS);
//-------------------------------------------------good
  starter=playerHead;
  currentPlayer=(PLAYER)(starter->item);//starts with player 1

  while(strcmp(currentItem->special, "WIN")!=0)
  {
    printf("It is %s's turn\n", currentPlayer->name);
    char *nextColor=processColor(randomNumber(4));
    printf("Rolled %s \n",nextColor);
    current=moveForward(current, nextColor, &breakPoint);
    if(breakPoint>500)
      return " ";

    currentItem=(SQUARE)(current->item);
    currentPlayer->currentSpace=currentItem;

    printf("Current square for %s is now \n",currentPlayer->name);
    printf("%s \n",toStringS(currentPlayer->currentSpace));

    if(strcmp(currentItem->special,"WIN")==0)
      break;

    if(starter->prev==NULL)
      starter=starter->next;
    else if(starter->next==NULL)
      starter=starter->prev;

    currentPlayer=(PLAYER)(starter->item);
    currentItem= (SQUARE)(currentPlayer->currentSpace);

    temp=otherCurrent;
    otherCurrent=current;
    current=temp;
  }

  strcpy(winner, currentPlayer->name);
  return winner;
}

LIST moveForward(LIST current, char* color, int *breaker)
{
  LIST temp=current;
  int infinite=0;
  while(compare(color, temp->next->item)!=0)
  {
    printf("Moving one space ahead\n");
    temp=temp->next;
    if(temp->next==NULL)
    {
      printf("Next color does not exist\n");
      return current;
    }
  }
  printf("Moving one space ahead\n");

  temp=temp->next;
  SQUARE currentItem= (SQUARE)(temp->item);//casts value of current generic
  while(strcmp(currentItem->special,"NONE")!=0&&strcmp(currentItem->special,"WIN")!=0)//if theres a special
  {
    if(strcmp(currentItem->special,"GOBACK")==0)
    {
      printf("Going back boys\n");
      for(int i=0;i<currentItem->x;i++)
      {
        printf("Moving back one space\n");
        if(temp->prev==NULL)
        {
          printf("Can't go back that much\n");
          *breaker=*breaker+1;
          return current;
        }
        temp=temp->prev;
      }
    }
    if(strcmp(currentItem->special,"GOFORWARD")==0)
    {
      printf("fast forward\n");
      for(int i=0;i<currentItem->x;i++)
      {
        printf("Moving forward one space\n");
        if(temp->next==NULL)
        {
          printf("Can't go forward that much\n");
          *breaker=*breaker+1;
          return current;
        }
        temp=temp->next;
      }
    }
    currentItem= (SQUARE)(temp->item);
    infinite++;
    if(infinite>500)
    {
      *breaker=1000;
      return temp;
    }

  }
  *breaker=0;
  return temp;
}

char* processColor(int i)
{
  char* color;
  color = (char*) malloc(sizeof(char)*20);
  if(i==1)
  {
    strcpy(color,"RED");
    return color;
  }
  else if(i==2)
  {
    strcpy(color,"BLUE");
    return color;
  }
  else if(i==3)
  {
    strcpy(color,"ORANGE");
    return color;
  }
  else if(i==4)
  {
    strcpy(color,"GREEN");
    return color;
  }
  strcpy(color,"ERROR");
  return color;
}

int randomNumber(int upperBound){
//this is the simple rn generator that generates a random number between 1 and upperBound
    int j;
    j=rand() % upperBound;
    return j+1;
}


SQUARE makeSquareNode(char buffer[])//reading for the inital file
{
  SQUARE S;
  char *color, *special, *x;
  int numX;
  color = (char*) malloc(sizeof(char)*20);
  special = (char*) malloc(sizeof(char)*20);
  x = (char*) malloc(sizeof(char)*20);

  color = strtok(buffer, " ");
  special = strtok(NULL, " ");
  x = strtok(NULL, " ");

  numX = atoi(x);
  S = newSquare(color, special, numX, toStringS);
  return S;
}
