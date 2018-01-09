#include<stdio.h>
#include<stdlib.h>
#include "river.h"

void del(node ** new,int rows)
{
   int i = 0;
   for(i = 0; i < rows;i++)
     {
        free(new[i]);
     }
  free(new);
}


void makeQueue(queue * elem,node ** matrix,int col,int row,int size)
{
  
  int i = 0;
  int j = 0;
  int count = 0;
  for(i = 0; i < row;i++)
  { 
    for(j = 0; j < col;j++)
        {
           
           matrix[i][0].distance = 0; 
           elem[count].p = &(matrix[i][j]);
           count++;
        }
  }
  //printf("%d\n",count);
}  
 
int compare(const void * a, const void * b)
{
   queue * ptr1 = (queue *)a; 
   queue * ptr2 = (queue *)b;
   queue elem1 = * ptr1;
   queue elem2 = * ptr2;

   return(elem1.p->distance - elem2.p->distance);
}
   


void dijkstra(queue * elem,node ** matrix, int size,int row,int col)
{
    
  
    node u = *(elem[0].p);
    while(size > 0)
    {
      u = *(elem[0].p);
      elem[0] = elem[size - 1];
      size--;
      qsort(elem,size,sizeof(queue),compare);
      //printf("%d %d %d %d %d\n",u.distance,u.Dedge->distance,u.Ledge->distance,u.Uedge->distance,u.Redge->distance);
     
     
   
      if(u.Dedge != NULL && (u.Dedge->distance > (u.distance + u.next.down)))
      {
         u.Dedge->distance = u.distance + u.next.down;
	 //printf("%d ",u.Dedge->distance);
      }
      if(u.Redge != NULL && (u.Redge->distance > (u.distance + u.next.right)))
      {
	 u.Redge->distance = u.distance + u.next.right;
	 //printf("%d ",u.Redge->distance);
      }
      if(u.Uedge != NULL && (u.Uedge->distance > (u.distance + u.next.up)))
      {
	 u.Uedge->distance = u.distance + u.next.up;
	 //printf("%d ",u.Uedge->distance);
      }
      if(u.Ledge != NULL && (u.Ledge->distance > (u.distance + u.next.left)))
      {
	 printf("%d",u.next.left);
         u.Ledge->distance = u.distance + u.next.left;
	 //printf("%d ",u.Ledge->distance);
      }
    }
}




node ** updateEdges(node ** mat,int ** txtmat,int row,int col)
{
  //change only right edges and downward edges
  int i = 0;
  int j = 0;
  for(i = 0; i < row - 1;i++)
  {
    for(j = 0; j < col;j++)
    {
       if (txtmat[i][j] == 1)
       {
          mat[i][j + 1].next.right = 1;
          mat[i][j + 1].next.down = 0;
          mat[i + 1][j +1].next.up = 0;
          mat[i + 1][j + 1].next.right = 1;
          mat[i][j + 2].next.left = 1;
          mat[i + 1][j + 2].next.left = 1;

          mat[i][j + 1].next.left = 1;
          mat[i + 1][j + 1].next.left = 1;
          
       }
    }
  }  
   return mat;
}

node ** setEdges(node ** adj,int row,int col)
{
  int i = 0;
  int j = 0;
  for(i = 0; i < row;i++)
     {
        for(j = 0; j < col;j++)
        {
           
           if(j != 0 && j != col - 1)
           {
              adj[i][j].Redge = &adj[i][j + 1];
              adj[i][j].Ledge = &adj[i][j - 1];
              
              adj[i][j].distance = 10 * col;
              adj[i][j].next.right = 2;
              
              if(i != 0)
              {
                 adj[i][j].next.up = 1;
                 adj[i][j].Uedge = &adj[i - 1][j];
              }
              if(i != row - 1)
              {
                adj[i][j].next.down = 1;
                adj[i][j].Dedge = &adj[i + 1][j];
              }
              if(j != 1)
              {
                adj[i][j].next.left = 2;
                
              }
              if(j == 1)
              {
                adj[i][j].next.left= 0;
              }
           }
           if(j == 0) 
           {
             adj[i][j].next.right = 0;
             adj[i][j].distance = 0;
             adj[i][j].Redge = &adj[i][j + 1];
             adj[i][j].Ledge = NULL;
             adj[i][j].Uedge = NULL;
             adj[i][j].Dedge = NULL;
             
           }
           if(j == col - 1)
           {
              adj[i][j].next.left = 2;
              adj[i][j].Ledge = &adj[i][j - 1];
              adj[i][j].distance = 10 * col;
              adj[i][j].Redge = NULL;
              adj[i][j].Uedge = NULL;
              adj[i][j].Dedge = NULL;
           }
        } 
     }  
  return adj;
}


node ** Load_From_File(char * filename, int * a)
{ 
  FILE * ptr = fopen(filename,"r");
  if(ptr == NULL)
   { 
     return NULL;
   }
   int col = 0;//number of integers per sequence
   int rows =  0;//number of rows
   int i = 0;
   int j = 0;
   fscanf(ptr,"%d %d\n",&rows,&col);
   //printf("Rows :%d\n",rows);
   //printf("Column :%d\n",col);
   

   //Make an adjacency matrix and initialize edges
   node ** start = NULL;
   start = malloc(sizeof(node*) * rows);
   for(i = 0; i < rows;i++)
     {
        start[i] = malloc(sizeof(node) * (col + 2));     
     }
    
    for(i = 0; i < rows;i++)
     {
        for(j = 0; j < col + 2;j++)
        {
           start[i][j].distance  = 0;
           start[i][j].next.up = 0;
           start[i][j].next.down = 0;
           start[i][j].next.left = 0;
           start[i][j].next.right = 0;
           start[i][j].Redge = NULL;
           start[i][j].Ledge = NULL;
           start[i][j].Dedge = NULL;
           start[i][j].Uedge = NULL;
           start[i][j].pred = NULL;
        }
       // printf("\n");
     }    

   node ** newmatrix = NULL;
    newmatrix =  setEdges(start,rows,col + 2);  
  //Fill the adjacency matrix with  structs at every [row][col]
  // Read the text file and store in matrix, compare with adjacency matrix and change values.
   int ** txtmat = NULL; 
   txtmat = malloc(sizeof(int*) * rows);
   for(i = 0; i < rows - 1;i++)
     {
        txtmat[i] = malloc(sizeof(int) * (col));
     }
  
   int x  = 0;
   int y = 0;
   char ch = '0';
   ch = fgetc(ptr);
   while(!feof(ptr))
   {
     if (ch == '0' || ch == '1')
     {
       txtmat[x][y] = ch - '0';
       y++;
     }
     if(y == col)
     {
       x++;
       y = 0;
     }
      ch = fgetc(ptr);
   }

   for(i = 0; i < rows - 1;i++)
     {
        for(j = 0; j < col;j++)
        {
            //printf("%d",txtmat[i][j]);
        }
        //printf("\n");
     }   
     
   node ** update = NULL;
   update = updateEdges(newmatrix,txtmat,rows,col);
   for(i = 0; i < rows;i++)
     {
        for(j = 0; j < col + 2;j++)
        {
           if(update[i][j].Redge != NULL) 
           {
            // printf("%d",update[i][j].next.right);
             //printf("%d",update[i][j].next.up);
            // printf("%d",update[i][j].next.down);
             //printf("%d",update[i][j].next.down);
           }
        }
       // printf("\n");
     } 
  
   //Make a priority queue of nodes
   //Run dijkstra's algorithm
   int size = 0;
   size = rows * (col + 2);
   queue * elem = NULL;
   elem = malloc(sizeof(queue) * size);
   elem->p = NULL;
   
  
 

  // elem->p->distance = 0;
    makeQueue(elem,update,col + 2,rows,size);
   for(i = 0; i < size;i++)
   {
     //printf("%d\n",elem[i].p->distance);
   }
   int moves = 2 * col;
   dijkstra(elem,update,size,rows,col + 2);
   for(i = 0; i < rows;i++)
   {
     if(update[i][col + 1].distance < moves)
     {
        moves = update[i][col + 1].distance;
        
     }  
     //printf("%d\n",update[i][col + 1].distance);
     
   }
   del(update,rows);
   for(i = 0; i < rows - 1;i++)
     {
        free(txtmat[i]);
     }
   free(txtmat);
   free(elem);
   fclose(ptr);
   *a = moves;
   return NULL;
}



