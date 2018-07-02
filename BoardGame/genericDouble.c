#include "genericDouble.h"
#include <assert.h>

LIST makeNewListNode(void * item){
  LIST p;
  p = (LIST) malloc(sizeof(node_t));
  p->item = item;
  p->next = NULL;
  p->prev = NULL;
  return p;
}

LIST insert_rear(LIST head,LIST m){
  /*note, this will always insert at the rear of the list*/
  LIST p;
  if (head==NULL)
    return m;
  p=head;
  //now move to the rear of the list
  while(p->next != NULL){
    p=p->next;
  }
  p->next = m;
  m->prev = p;

  return head;
}


LIST findEnd(LIST head)
{
  LIST p;
  p=head;
  while(p->next!=NULL){
    p=p->next;
  }
  return p;
}

void displayForward(LIST m, void (*printFunction)(void * A)){
  LIST temp;
  int cnt=0;
  temp = m;
  if (temp==NULL){
    puts("NO LINKED LIST");
    return;
  }
  printf("node values are:\n");
  while (temp != NULL){
    printFunction(temp->item);
    temp=temp->next;
    cnt++;
  }
  printf("%d students were found\n",cnt);
}

void displayBackward(LIST m, void (*printFunction)(void * A))
{
  LIST temp;
  int cnt=0;
  temp = m;
  if (temp==NULL){
    puts("NO LINKED LIST");
    return;
  }
  printf("node values are:\n");
  while (temp != NULL){
    printFunction(temp->item);
    temp=temp->prev;
    cnt++;
  }
  printf("%d students were found\n",cnt);
}

void printNodeN(LIST head, int id,void (*printFunction)(void * A))
{
  LIST temp;
  int cnt=1;
  temp = head;
  if (temp==NULL){
    puts("NO LINKED LIST");
    return;
  }
  while (temp != NULL){
    if(cnt==id){
      printFunction(temp->item);
      break;
    }
    temp=temp->next;
    cnt++;
  }
  if(cnt<id)
    printf("Node could not be printed\n");
}

LIST deleteIt(LIST head, void * itemToBeRemoved, int (*compare)(void * A, void * B), int *success){
  LIST p =head;
  LIST temp=head;
  if(temp==NULL)
    return p;
  while(p!=NULL)
  {
    if(compare(itemToBeRemoved,p->item)==0)//sees if nodes are the same
    {
      *success=1;
      temp=p;//free this
      if(p->next==NULL&&p->prev==NULL)//if p is the only node//check later
      {
        free(p);
        return NULL;
      }
      if(p->next==NULL)//if node to be deleted is at end
      {
        p->prev->next=NULL;
        free(p);
        return head;
      }
      else if(p->prev==NULL&&p->next!=NULL)//if node to be deleted is in front
      {
        p=p->next;
        p->prev=NULL;
        free(temp);
        return p;
      }
      else//if node to be deleted is in the middle
      {
        p->prev->next=p->next;
        p->next->prev=p->prev;
        free(p);
        return head;
      }
    }
    p=p->next;
  }
  return head;
  }
