#ifndef PA02_H
#define PA02_H
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
  long value;
  struct Node * next;
}Node;

typedef struct List {
Node *node;
struct List *next;
} List;

Node * Load_From_File(char * Filename);
int Save_To_File(char * Filename,Node *List);
Node * Shell_Insertion_Sort(Node * List,double * N_Comp,double * N_Moves);
#endif
