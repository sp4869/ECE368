#include<stdio.h>
#include<stdlib.h>
#include "genome.h"
static int ** Load_From_File(char *Filename, int * a,int * b,int ** adj,FILE * ptr)
{
  int rows = 0;
  int col = 0;
  int i = 0;
  int j = 0;
  rows = *a;
  col = *b;
  //FILE * ptr = NULL;
  //ptr = fopen(Filename,"rb");
  if(ptr == NULL)
  {
    return NULL;
  }
  for(i = 0; i < rows;i++)
     {
        for(j = 0; j < col;j++)
        {
          fread(&adj[i][j],sizeof(int),1,ptr);
        }
     }   
  //fclose(ptr); 
  return adj;
}

static void delete(int ** new,int rows)
{
   int i = 0;
   for(i = 0; i < rows;i++)
     {
        free(new[i]);
     }
  free(new);
}
static int * singleArrayEdge(int col)
{
    int i = 0;
    int * array = malloc(sizeof(int) * col);
    for(i = 0; i < col; i++) {
        array[i] = -1;
    }
    return array;
}

static int ** setEdgesZero(int ** adj,int col)
{
  int i = 0;
  int j = 0;
  for(i = 0; i < col;i++)
     {
        for(j = 0; j < col;j++)
        {
           adj[i][j] = 0;
        }
     }   
  return adj;
}

static int ** setedgesOne(int ** adj,int ** initialize,int rows, int col)
{
 // int i = 0;
  int j = 0;
  int k = 0;
 // int x = 0;
  int z  = 0;
  //int edges = 0;
  int ** newmatrix = initialize;
//Create the adjacency matrix using the first sequence

for(k = 0;k < rows;k++)
{  
  for(j = 0; j < col;j++)
  {
     for(z = j + 1; z < col;z++)
     {
        if(k == 0)
        {
          newmatrix[adj[0][j]- 1][adj[0][z] - 1] = 1;
        }
        else
        {
          if(newmatrix[adj[k][j] - 1][adj[k][z] - 1] == 0)
          {
            newmatrix[adj[k][z] - 1][adj[k][j] - 1] = 0;
          }
        }
     }
   }
}
  return newmatrix;
}

static void DFS(int ** new, int row, int col, int size, int length, int * x, int * array, int * answer)
{
    int i = 0;
    int k = 0;
    if (new[row][col] == 0)
    {
        while (k < size && array[k] != -1)
        {
           k++;
        }
        array[k] = row + 1;
        if (length > *x)
        {
            *x = length;
            for (i = 0; i < length; i++)
            {
                answer[i] = array[i];
                
            }
        }
        
        return;
    }
    int L = 0;
    int z  = 0;
    while (L < size && array[L] != -1)
    {      
        L++;
    }
    array[L] = row + 1;
    for(i = 0; i < size; i++)
    {
        DFS(new, col, i, size ,length + 1, x, array, answer);
        //free(answer);
         z = 0;
        while (z < size && array[z] != -1)
        {      
            z++;
        }
        array[z-1] = -1;
    }
}      


static int * calcLength(int ** new, int col, int * final)
{
   int i = 0;
   int j = 0;
   int k = 0;
   int length = 0;
   int count = 0;
   int * result = NULL;
   int * array = NULL;
   int * answer = NULL;
   result = singleArrayEdge(col);
   //array = singleArrayEdge(col);
   //answer = singleArrayEdge(col);
   for (i = 0; i < col; i++)
   {
      for(j = 0; j < col; j++)
      {
         if (new[i][j] == 1)
          {
             int x = 0; 
             array = singleArrayEdge(col);
             answer = singleArrayEdge(col);
             DFS(new, i, j, col, 1, &x, array, answer);
             
             if (x > length)
             {
                //result = singleArrayEdge(x);
                count++;
                for (k = 0; k < x; k++)
                {
                     result[k] = answer[k];
                     //printf("%d\n",result[k]);
                }
                //printf("Hell");
                length = x;      
             }
             free(answer);
             free(array);
             
           }
           
      }
       
   }
    if(count == 0)
    {
       length = 1;
      //result[count] = new[0][0];
     }
     
    //printf("%d\n",count);
    *final = length;
    return result;
}
   

int * Longest_conserved_gene_sequence(char *filename, int *size_of_seq)
{
 
    
   FILE * new = fopen(filename,"rb");
   if(new == NULL)
   {
      *size_of_seq = 0; 
      return NULL;
   }
   int newsize[2];
   int col = 0;//number of integers per sequence
   int rows =  0;//number of sequences
   int i = 0;
   int j = 0;
   fread(newsize,sizeof(int),2,new);
   col = newsize[0];
   rows = newsize[1]; 
   //Create a 2d matrix which contain the sequence
   int ** start = malloc(sizeof(int*) * rows);
   for(i = 0; i < rows;i++)
     {
        start[i] = malloc(sizeof(int) * col);
     }
   static int ** a = NULL;
   a = Load_From_File(filename, &rows,&col,start,new);
   
  /*for(i = 0; i < rows;i++)
     {
        for(j = 0; j < col;j++)
        {
          printf("%d ",a[i][j]);
        }
        printf("\n");
     }    
   */
   
  //Create an adjacency 2D matrix which is filled with 0's
   int ** adj = NULL;

   adj = malloc(sizeof(int*)* col);
   for(j = 0; j < col;j++)
     {
        adj[j] = malloc(sizeof(int) * col);
     }
   static int ** initialize = NULL;
   initialize = setEdgesZero(adj,col);
   /*for(i = 0; i < col;i++)
     {
        for(j = 0; j < col;j++)
        {
          printf("%d ",initialize[i][j]);
        }
        printf("\n");
     }  */  
 
  //setEdges to 1 based off the sequence
    static int ** newmatrix = NULL;
    newmatrix =  setedgesOne(a,initialize,rows,col);

    //Calculate the length of the sequence
    
    static int * seq = NULL;
    int length = 0;


    seq = calcLength(newmatrix, col, &length);
    if(length == 1)
    {
      seq[length - 1] = a[0][0];
    }
    delete(start,rows);
    delete(adj,col);
    //for (i = 0; i < length; i++) {
       // printf("%d\n",seq[i]);
    //} 
  // free(seq);
   *size_of_seq = length;
   fclose(new);
   return seq;
}

