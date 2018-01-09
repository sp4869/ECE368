#ifndef PA06_H
#define PA06_H

typedef struct Edges{
      int right;
      int down;
      int up;
      int left;
      
}Edges;

typedef struct node{
      int distance;
      Edges next;
      struct node * Redge;
      struct node * Ledge;
      struct node * Uedge;
      struct node * Dedge;
   
}node;

typedef struct queue{
     node * p;
}queue;

node ** Load_From_File(char * filename, int * a);
node ** setEdges(node ** adj,int row,int col);
node ** updateEdges(node ** mat,int ** txtmat,int row,int col);
int compare(const void * a, const void * b);
void makeQueue(queue * elem,node ** graph,int col,int row,int size);
void dijkstra(queue * elem,node ** matrix, int size,int row,int col);
void del(node ** newmatrix,int rows);
//void Downward_heapify(queue * elem,int i,int size);
//void enqueue(queue * elem,node * u,int * front,int size);
#endif
