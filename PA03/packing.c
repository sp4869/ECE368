#include<stdio.h>
#include<stdlib.h>
#include "packing.h"

void findmax(bnode * root,int * p)
{
  if(root ==  NULL)
  {
     return;
  }
  findmax(root->left,p);
  findmax(root->right,p);
  if(root->letter == 0)
  {
    *p = max(*p,root->label);
  }
}
void findnode(bnode * root,int num,double * xcor,double * ycor)
{ 
  if(root == NULL)
  {
    return;
  }
  if(root -> label == num)
  {
     *xcor = root->x_coord;
     *ycor = root-> y_coord; 
     return;
  }
  findnode(root->left,num,xcor,ycor);
  findnode(root->right,num,xcor,ycor);
}
void checktree(bnode * root,int * p)
{
  if(root == NULL)
  {
    return;
  }
  checktree(root->left,p);
  checktree(root->right,p);
  if(root->letter == 'V') 
  {
     if(root->left == NULL && root->right == NULL)
     {
        *p = 1;
         return;
     }
  }
  if(root->letter == 'H')
  {
     if(root->left == NULL || root->right == NULL)
     {
        *p = 1;
        return;
     }
  }
  if(root->letter == 0)
  {
    if(root-> left != NULL || root->right != NULL)
    {
        *p = 1;
        return;
    }
  }
} 


Stack * createstack(int size)
{
  Stack * stack = malloc(sizeof(Stack));  
  stack -> size = size;
  stack -> top = -1;
  stack -> array =  malloc(size * sizeof(bnode));
  return stack;
}


int isFull(Stack * stack)
{
  if((stack->top - 1) == stack->size)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
int isEmpty(Stack * stack)
{
  if(stack->top == -1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void push(Stack * stack,bnode * root)
{
  int y = 0;
  if(isFull(stack))
  {
    return;
  }
  stack ->top = stack->top + 1;
  y = stack->top;
  stack->array[y] = root;
}

bnode * pop(Stack * stack)
{
  if(isEmpty(stack))
  {
    return NULL;
  }
  int x = stack->top;
  bnode * root = (stack->array)[x];
  stack->top = stack->top - 1;
  return(root);
}


bnode * create_node(int value,double w,double h,char c)
{
  bnode * root = malloc(sizeof(bnode));
  root -> left = NULL;
  root -> right = NULL;
  root -> width = w;
  root -> height = h;
  root -> label = value;
  root -> letter = c;
  root -> x_coord = 0;
  root->  y_coord = 0;
  return root;
}
  
void destroy_tree(bnode * root)
{
  if(root == NULL)
  {
    return;
  }
  destroy_tree(root->left);
  destroy_tree(root-> right);
  free(root);
}
bnode * load_tree_from_file(char * filename)
{
  char ch = 0;
  int count = 0;
  int i = 0;
  int value = 0;
  double width = 0;
  double height = 0;
  FILE * ptr = fopen(filename,"r");
  if (ptr == NULL)
  {
    return NULL;
  }
 
  while(!feof(ptr))
  {
    ch = fgetc(ptr);
    if(ch == '\n')
    {
      count++;
    } 
  }
  fseek(ptr,0,SEEK_SET);
  Stack * stack = createstack(count);
  bnode * root = NULL;
  char a = 0;
  int x = 0;
  //create stack function,set top to -1 etc..
   for(i = 0;i < count;i++)
  {  
    x = fscanf(ptr,"%d(%le,%le)\n",&value,&width,&height);
    if(x == 3)
    {
      root = create_node(value,width,height,0);
      push(stack,root);  
    }
    else
    {
      fscanf(ptr,"%c\n",&a);
      root = create_node(0,0,0,a);
      root->right = pop(stack);
      root->left = pop(stack);
      push(stack,root);
    }
  } 
  
  stack->top--;
  while(stack->top != -1)
  { 
     free(stack->array[stack->top]);
     stack->top--;
  } 
 // root = pop(stack);
  free(stack->array);
  free(stack);
  fclose(ptr);
  return root;
}  

int save_file(char * filename,bnode * root)
{
  if(root == NULL)
  {
    return 0;
  }
  FILE * ptr = fopen(filename,"w");
  if(ptr == NULL)
  {
    return 0;
  }
  postorder(root,ptr);
  fclose(ptr);
  return 1;
}

void packing(bnode * root)
{
  if(root->left == NULL && root->right == NULL)
  {
    return;
  } 
  if(root-> letter == 'H')
   {
     packing(root->right);
     packing(root->left);
     root->height = (root->right)->height + (root->left)->height;
     root->width = max((root->right)->width,(root->left)->width);
     root->x_coord = root->x_coord;
     root->y_coord = (root->right)->height;
     update_coord(root->left,&(root->x_coord),&(root->y_coord));  
     
   }
  
  if(root-> letter == 'V')
   {
     packing(root->left);
     packing(root->right);
     root->width = (root->right)->width + (root->left)->width;
     root->height = max((root->right)->height,(root->left)->height);
     root->x_coord = (root->left)->width;
     root->y_coord = root->y_coord;
     update_coord(root->right,&(root->x_coord),&(root->y_coord));
   }

}

void update_coord(bnode * root,double * val1,double * val2)
{
  if(root == NULL)
  {
    return;
  }
  root->x_coord = root->x_coord + *val1;
  root->y_coord = root->y_coord + *val2;
  update_coord(root->left,val1,val2);
  update_coord(root->right,val1,val2);  
}

int max(double a ,double b)
{
  if (a > b)
  {
    return a;
  }
  return b;
} 

void postorder(bnode * root,FILE * ptr)
{
  if(root == NULL)
  {
    return;
  }
  postorder(root->left,ptr);
  postorder(root->right,ptr);
  if(root->letter == 0)
  {
   fprintf(ptr,"%d %le %le %le %le\n",root->label,root->width,root->height,root->x_coord,root->y_coord);
  } 
  else
  {
    return;
  }

}
