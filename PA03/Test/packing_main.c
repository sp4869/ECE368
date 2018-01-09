#include<stdio.h>
#include<stdlib.h>
#include "packing.h"

int main(int argc,char ** argv)
{
  double xcor = 0;
  double ycor = 0;
  int save = 0;
  int check = 0;
  if(argv[1] == NULL || argv[2] == NULL)
  {
    return EXIT_FAILURE;
  }
  bnode * root = NULL;
  if(argv[1])
  {
    root = load_tree_from_file(argv[1]);
  }
  bnode * stem = root;  
  checktree(stem,&check);
  if(check == 1)
  {
    destroy_tree(root);
    return EXIT_FAILURE;
  }
  packing(root);
  if(argv[2])
  {
    save = save_file(argv[2],root);
  }
  printf("Width: %le\n",root->width);
  printf("Height: %le\n",root->height);
  findmax(root,&check);
  //printf("%d\n",check);
  findnode(root,check,&xcor,&ycor);
  printf("X-coordinate: %le\n",xcor);
  printf("Y-coordinate: %le\n",ycor);
  destroy_tree(root);
  return EXIT_SUCCESS;
}
