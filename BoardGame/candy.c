#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "genericDouble.h"
#include "square.h"


SQUARE makeSquareNode(char buffer[]);
LIST readFile();
int playGame(LIST head, LIST end);
LIST moveForward(LIST current, char *color, int *breaker);
char* processColor(int i);
int randomNumber(int upperBound);

int main(int argc, char *argv[]){
  srand(time(NULL));
  LIST head, end;//*node_t
  head=NULL;
  end=NULL;
  int gameWin=0;
  int sum=0;
  head=readFile();
  if(head!=NULL)
    end=findEnd(head);
  for(int i=0;i<5;i++)
  {
    printf("This is the board\n");
    displayForward(head,printIt);
    gameWin= playGame(head,end);
    if(gameWin==0)
      printf("High likelihood this game cannot be won\n");
      else
      printf("It took %d turns to win\n", gameWin);
      sum+=gameWin;
  }
  printf("Average number of turns to win 5 games is %d\n", sum/5);
  printf("Done\n");
  LIST deleter =head;
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

int playGame(LIST head, LIST end)
{
  if (head==NULL)
    return 0;
  int i;
  int count=0;
  int breakPoint=0;//detects for infinite loops
  LIST current=head;
  SQUARE currentItem= (SQUARE)(current->item);
  while(strcmp(currentItem->special,"WIN")!=0)
  {
    int i=randomNumber(4);
    char *nextColor=processColor(i);
    printf("Rolled %s \n",nextColor);
    current=moveForward(current, nextColor, &breakPoint);//updates current
    if(breakPoint>500)
      return 0;
    printf("Current square is now \n");
    printf("%s \n",toStringS(current->item));
    currentItem= (SQUARE)(current->item);
    count++;
  }
  printf("We won boys\n");
  return count;//counts to win
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
      printf("Next color does not exist\n");//if there isn't another occurence of nextColr
      return current;
    }
  }
  printf("Moving one space ahead\n");

  temp=temp->next;
  SQUARE currentItem= (SQUARE)(temp->item);//casts value of current generic
  while(strcmp(currentItem->special,"NONE")!=0&&strcmp(currentItem->special,"WIN")!=0)//if theres a special
  {
    if(strcmp(currentItem->special,"GOBACK")==0)//goback detected
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
    if(strcmp(currentItem->special,"GOFORWARD")==0)//goforward detected
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

char* processColor(int i)//converts number to color
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


SQUARE makeSquareNode(char buffer[])//process string information
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
  S = newSquare(color, special, numX, toStringS);//ask signorile about this later
  return S;
}
