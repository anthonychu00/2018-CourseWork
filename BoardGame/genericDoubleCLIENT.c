#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "genericDouble.h"
#include "student.h"

int menu();
STUDENT makeStudentNode(char buffer[]);
LIST insertManually(LIST head);
LIST delete(LIST head);
LIST readFile();

int main(int argc, char *argv[]) {
  LIST head, end;//*node_t
  char* inputID;
  int id;
  int answer;
  head=NULL;
  end=NULL;
  inputID = (char *) malloc(sizeof(char) * 20);
  while(1){
    answer = menu();
    switch (answer){
      case 0:
      {
        head = readFile();
        if(head!=NULL)
          end = findEnd(head);
        else
          end=NULL;
        break;
      }
      case 1:{
        displayForward(head,printIt); // printIt is defined in stock.h
        break;
      }
      case 2:{
        displayBackward(end,printIt);
        break;
      }
      case 3:{
        head = delete(head);
        if(head!=NULL)
          end = findEnd(head);
        else
          end=NULL;
        break;
      }
      case 4:{
        printf("Choose nth student to print. \n");
        scanf("%s",inputID);
        id=atoi(inputID);
        printNodeN(head,id,printIt);
        break;
      }
      case 5:{
        head =insertManually(head);
        if(head!=NULL)
          end = findEnd(head);
        else
          end=NULL;
        break;
      }
      case 6:{
        printf("goodbye\n");
        LIST deleter =head;
        while(deleter){
          LIST del =deleter;
          deleter=deleter->next;
          free(del);
        }
        exit(0);
      }
    }
  }
}

LIST readFile(){
  FILE *inf = fopen("student.txt", "r"); //opens a file for READING
  char buffer[80];
  STUDENT S;
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
    S = makeStudentNode(buffer);
       count++;
    l = makeNewListNode(S);
    head =  insert_rear(head,l);//now you need to insert the stock into a node of the generic link list
  }

  fclose(inf);  //Closes a file.
  printf("%d new records were read\n", count);
  return head;
  //Hopefully, at this point, the data is nicely stored in the generic link list
}

LIST insertManually(LIST head)
{
  STUDENT s;
  LIST l;
  char *str, *str2;
  int id=0;
  str = (char *) malloc(sizeof(char) * 40);
  str2 = (char *) malloc(sizeof(char) * 40);
  printf("Please enter the student id\n");
  fgets(str,40,stdin);
  printf("And what is their name?\n");
  fgets(str2,40,stdin);

  id=atoi(str);
  s=newStudent(id,str2,toString);
  l=makeNewListNode(s);
  head=insert_rear(head,l);
  return head;
}

LIST delete(LIST head){
  STUDENT s;
  LIST temp;
  char *id;
  int success;
  if (head == NULL){
    printf("NO LIST DUMMY\n");
    return head;
  }
  id = (char *) malloc(sizeof(char) * 20);
  printf("what student do you want to delete(name please)?\n");
  fgets(id,20,stdin);
  temp = deleteIt(head, id , compare, &success); //remember compare is in stock.h //deleteIT found in generic
  if (success == 0)
    printf("student %s not found in list\n",id);
  else
    printf("student %s succesfully deleted from list\n",id);
  return temp;
}

STUDENT makeStudentNode(char buffer[])//reading for the inital file
{
  STUDENT S;
  char *id, *name;
  int numId;
  id = (char*) malloc(sizeof(char)*20);
  name = (char*) malloc(sizeof(char)*20);

  id = strtok(buffer, " ");
  name = strtok(NULL, "\0");

  numId = atoi(id);
  S = newStudent(numId, name, toString);
  return S;
}

int menu(){
  int a;
  char carraigeReturn;
  //puts("welcome to student generics");
  puts("Please choose from the following choices");
  puts("0. Read from a file");
  puts("1. List all the students using toString");
  puts("2. List all students backward");
  puts("3. Delete a student");
  puts("4. Print an individual student");
  puts("5. Insert another student at the end");
  puts("6. Quit and leave");
  scanf("%d%c", &a, &carraigeReturn);
  return a;
}
