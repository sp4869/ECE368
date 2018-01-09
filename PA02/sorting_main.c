#include <stdlib.h>
#include "sorting.h"
#include <stdio.h>
#include<string.h>
#include<time.h>

Node * create_node(long val);
void destroy_node(Node * list);
long power(long a,long b);
Node * GenSeq(int Size,long * count);
Node * reverse_list(Node * list);
Node * traverse(Node * list,int i);
Node * LastSort(Node * head);
List * CreateList(int num);
void destroy_list(List * list);
Node * insertion_sort(Node * head);
Node * insertion_sort_helper(Node * head, Node * current);
void PrintList(Node * head);
int main(int argc ,char ** argv)
{
  clock_t startIO;//starts recording runnning time of program
  clock_t stopIO;//stops recording running time of program
  clock_t startSort;//starts recording time to sort
  clock_t stopSort;//stops recording time to sort
  long count  = 0;
  double a = 0;
  double b = 0;
  if(argv[1] == NULL || argv[2] == NULL)
  {
    return EXIT_SUCCESS;
  }
  startIO = clock();
  Node * temp = NULL;
  if(argv[1]) 
  {
   temp = Load_From_File(argv[1]);
  }
  startSort = clock();
  Node * sort = Shell_Insertion_Sort(temp,&a,&b);
  Node * top = sort;
  stopSort = clock();
  /*while(sort != NULL)
  {
    printf("%lu\n",sort->value);
    sort = sort->next;
    count++;
  }*/
  
  int savebinary = 0;
  if(argv[2])
  {
    savebinary = Save_To_File(argv[2],sort);
  }
  //destroy_node(temp);
  sort = top;
  destroy_node(sort);
  stopIO = clock();
  
  printf("Number of long integers read: %lu\n",count);
  printf("Number of long integers stored: %lu\n",count);
  printf("I/O time: %f\n",((double)(stopIO - startIO)) / CLOCKS_PER_SEC);
  printf("Sorting time: %f\n",((double)(stopSort - startSort)) / CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}
