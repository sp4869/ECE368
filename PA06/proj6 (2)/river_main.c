#include<stdio.h>
#include<stdlib.h>
#include "river.h"
int main(int argc,char ** argv)
{
  if(argv[1] == NULL)
  {
    return EXIT_FAILURE;
  }
  node ** load = NULL;
  int a = 0;
  if(argv[1])
  {
     load = Load_From_File(argv[1],&a);
  }
  printf("%d\n",a);
  return EXIT_SUCCESS;

}
