#include<stdio.h>
#include<stdlib.h>
#ifndef PA03_H
#define PA03_H

typedef struct bnode{
   double area;
   double width;
   double height;
   double x_coord;
   double y_coord;
   int label;
   char letter;
   struct bnode * left;
   struct bnode * right;
}bnode;


typedef struct Stack{
    int top;
    struct bnode ** array;
    int size;
}Stack;

bnode * load_tree_from_file(char * filename, int * a);
bnode * create_node(int a,double b,double c,char d);
int save_file(char * filename,bnode * root);
void destroy_tree(bnode * root);
bnode * pack(bnode * root);
Stack * createstack(int size);
int isFull(Stack * stack);
int isEmpty(Stack * stack);
void push(Stack * stack,bnode * node);
bnode * pop(Stack * stack);
void postorder(bnode * root,FILE * ptr);
int max(double a ,double b);
void packing(bnode * root);
void update_coord(bnode * root,double * val1,double * val2);
int save_file(char * filename,bnode * root);
void findmax(bnode * root,int * b);
void checktree(bnode * root,int * a);
void findnode(bnode * root,int num,double * xcor,double * ycor);
void reroot(bnode * root,bnode * node1,bnode * node2,double * a,double * b);
bnode * reorganize(char a,bnode * left,bnode * right);
void rerooting(bnode * root);
#endif


   
