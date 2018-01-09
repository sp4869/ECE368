#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "sorting.h"

Node * create_node(long val)
{
  Node * node = malloc(sizeof(Node));
  node -> value = val;
  node -> next = NULL;
  return node;
}

Node * reverse_list(Node * list)
{
  if(list == NULL)
  {
    return NULL;
  }
  Node * curr = list;
  Node * temp = list;
  Node * prev = NULL;//has to be set to NULL
  while(curr != NULL)
  {
    temp = curr->next;//points to the next element current points to
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  return prev;
}
void destroy_node(Node * list)
{
  Node * temp = list;
  while(temp != NULL)
  {
    temp = temp->next;
    free(list);
    list = temp;
  }
}

long power(long a,long b)
{
  long i = 0;
  long j = 0;
  long x = 1;
  long y = 1;
  while (i < a)
   {
     x = 2 * x;//calculates 2^p
     i++;
   }
  while(j < b)
   {
     y = y * 3;//calculates 3^q
     j++;
   }
   return(x * y);//return 2^p * 3^q
}
Node * GenSeq(int Size,long * count)
{
  int length = 0;
  int i = 0;
  int j = 0;
  long value = 0;
  //long * arrayel = malloc(sizeof(long) * Size);
  Node * head = NULL;
  Node * tail = NULL;
  for (i = 0; i < Size;i++)
  { 
     for(j = 0; j <= i; j++)
     {
        value = power(i - j,j);//pow(2,i -j) * pow(3,j)
        if (value < Size)
        {
           Node * curr = create_node(value);
           if(tail != NULL)
	   {
              tail->next = curr;//connects the nodes
              tail = curr;//advances the tail
           }
           else
           {
	     head = curr;//sets head and tail towards current value;
             tail = curr;
           } 
           length++;
           //printf("%lu\n",arrayel[k]);
           *count = length;
        }
        else
        {
           if(power(i + 1, 0) > Size)//pow(2,i +1) * pow(3,0)
              {
                 return head;            // go to the next row calculate first element of the next row
              }
           j = i + 1;
        }  
      }
  }  
  return head;
}

Node * traverse(Node * list,int i)
{
   
   Node * curr = list;
   if(i < 0)
   {
      return NULL;
   }
   while(i > 0 && (curr != NULL))
   {
     curr = curr->next;
     i--;
   }
   return curr;
}

void LastSort(Node * head,int size,Node * temp1,Node * temp2)
{
   int i = 0;
   int j = 0;
   int length = size;
   long value = 0;
    for (j = 1;j < length;j++)
        {
           temp2 = traverse(head,j);//temp1 is at the node j away from the head   
           if(temp2 != NULL)
           {
             value = temp2->value;
           }
           for(i = j;i > 0;i--)
           {
 
              temp1 = traverse(head,i - 1);
              if(temp1 != NULL && temp2 != NULL)
              {
                 if(temp1->value > value)
                 {       
                    temp1->next = temp2->next;
                    temp2 -> next = temp1;             
                    if(temp1 == head)
                    {
                       head = temp2;
                    }
                 }
                else
                {
                  temp1->next = temp2;
                  i = 0;
                }
              } 
            }
         }
    //free(seq);
    //return head;

}

Node * Shell_Insertion_Sort(Node * list,double *N_Comp, double *N_Move)
{
    long count = 0;
    int length = 0;
    Node * head = list;//points to the head of the linked list.
    Node * curr = list;
    while(curr != NULL)
    {
       curr = curr -> next;
       length++;//finds the length of the linked list.
    } 
    Node * seq = GenSeq(length,&count);//generates the sequence
    Node * new = reverse_list(seq);
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    long value = 0;
    Node * temp1 = NULL;
    Node * temp2 = NULL;
    Node * prev_temp2 = NULL;    
    Node * prev_temp1 = NULL; 
    Node * next_temp2 = NULL;  
    Node * next_temp1 = NULL;
   // Node * travel = head;
   // Node * prev_travel = NULL;
    //temp1 is to the left of temp2
    while(new != NULL) //shell sort loop
    {
        k = new -> value;
        for (j = k;j < length;j++)
        {
           temp2 = traverse(head,j);//temp1 is at the node j away from the head   
           next_temp2 = temp2->next;
           
           if(temp2 != NULL) //&& prev_temp2 != NULL)
           {
             value = temp2->value;
           }
           f = j % k;
           temp1 = traverse(head,f);
           //printf("%d\n",f);
           next_temp1 = temp1->next;
           while (temp1->value <  value)
           {
              f = f + k;
              temp1 = traverse(head,f);
              next_temp1 = temp1->next;
           }
           if(temp1->value > value)
           {       
              prev_temp2 = traverse(head,j - 1);
              temp1->next = temp2->next;
                
               if(temp1 != head)//prev_temp1 != NULL
                 {
                      prev_temp1 = traverse(head,f - 1);                     
                      prev_temp1 -> next = temp2;     
                 }    
               else
                 {
                    //if(temp1 == head)
                      head = temp2;
                  }                          
               if(prev_temp2 != temp1 && next_temp1 != temp2)
                 {
                    prev_temp2 -> next = temp1;
                    temp2 -> next = next_temp1;
                 }
               else
                 {
                    temp2->next = temp1;
                 }
                              
           }
      
      }
      new = new ->next;
  }
    destroy_node(seq);
    destroy_node(new);
    return head;
}

Node * Load_From_File(char * Filename)
{
   FILE * ptr = NULL;
   Node * head = NULL;
   Node * tail = NULL;
   ptr = fopen(Filename,"rb");
   if (ptr == NULL)
   {
      return NULL;
   }
   //printf("%lu\n",count);
   // the number of long integers has now been found
   //the list should now be read and inputted into a linked list
   long val = 0;
   int sum = 0;
   while(fread(&val,sizeof(long),1,ptr))
     {
       Node * curr = create_node(val);
       if(tail != NULL)
	 {
           tail->next = curr;
           tail = curr;
         }
       else
         {
	   head = curr;
           tail = curr;
         } 
       // printf("%lu\n",curr->value);
     }
       sum++; 
   fclose(ptr);
   return head;
}
int Save_To_File(char * Filename,Node *list)
{
  FILE * ptr = NULL;
  ptr = fopen(Filename,"wb");
  //List points to the head of the linked list
  if(ptr == NULL)
  {
    return 0;
  }
  Node * head = list;
  int count = 0;
  while(head != NULL)
  {
     fwrite(&(head->value),1,sizeof(head->value),ptr);
     head = head -> next;
     count++;
  }
  fclose(ptr);
  return count;
}


