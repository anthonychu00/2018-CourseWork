#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    void *item;
    struct node *next;
    struct node *prev;
}node_t;

typedef node_t *LIST;//shortcut for a pointer to a list

LIST makeNewListNode(void * item);
LIST findEnd(LIST head);
LIST insert_rear(LIST head, LIST n);
void displayForward(LIST m, void (*printFunction)(void * A));
void displayBackward(LIST m, void (*printFunction)(void * A));
void printNodeN(LIST head, int id,void (*printFunction)(void * A));
LIST deleteIt(LIST head, void * itemToBeRemoved, int (*compare)(void * A, void * B), int *success);
