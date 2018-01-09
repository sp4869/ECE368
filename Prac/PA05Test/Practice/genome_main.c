#include<stdio.h>
#include<stdlib.h>
#include "genome.h"

int main(int argc,char * argv[])
{
  int i = 0;
  int size_of_seq = 0;
  int * c = NULL;
  if(argv[1] == NULL)
  {
    return EXIT_FAILURE;
  }
  if(argv[1])
  {
    c = Longest_conserved_gene_sequence(argv[1],&size_of_seq);
  }
  for (i = 0; i < size_of_seq; i++)
  {
        printf("%d\n",c[i]);
    } 
  printf("Length:%d\n",size_of_seq);
  free(c);
  return EXIT_SUCCESS;
}
