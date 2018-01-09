#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>


void PrintList(Node * head)
{
  Node * temp = head;
  while(temp != NULL)
  {
     printf("%lu\n",temp->value);
     temp = temp->next;
  }
}

List * CreateList(int num)
{
   //Make  a sequence of lists which are connected to one another
   //set their nodes to null
   List * newlist = NULL;//pointer to  a list
   int i = 0;
	
   while(i < num)
    {
      List * new = malloc(sizeof(List));
      new ->node = NULL;
      new -> next = newlist;
      newlist = new;
      i++;
	//x++;
    }

	//printf("num of LLs - %d\n", x);
   return newlist;
}

Node * create_node(long val)
{
  Node * node = malloc(sizeof(Node));
  node -> value = val;
  node -> next = NULL;
  return node;
}

void destroy_node(Node * list)
{
  Node * temp = list;
	int x = 0;
  while(temp != NULL)
  {
    temp = temp->next;
    free(list);
    list = temp;
	x++;
  }
	//printf("num of nodes destroyed - %d\n", x);
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

void destroy_list(List * list)
{
	
   List * temp = list;
   if(list == NULL)
   {
      return;
   }
   //List * temp = list;
   /*destroy_list(list->next);
   free(list->node);
   free(list);
}*/
   while(list != NULL)
   {
     temp = list->next;
     free(list->node);
     free(list);
     list = temp;
	//x++;
   }
	

}
Node * LastSort(Node * head)
{
   int i = 0;
   int j = 0;
   Node * temp= head;
   long length = 0;
   while(temp != NULL)
   {
      temp = temp->next;
      length++;
   }
   Node * temp1 = NULL;
   Node * temp2 = NULL;
  
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
    return head;

}


Node * Shell_Insertion_Sort(Node * list,double *N_Comp, double *N_Move)
{
    long count = 0;
    int length = 0;
    Node * len = list;
    Node * head = list;
    while(len != NULL)
    {
       len = len -> next;
       length++;//finds the length of the linked list.
    } 
    if(length == 1)
    {
      return list;
    }
    Node * seq = GenSeq(length,&count);//generates the sequence
    Node * rev = reverse_list(seq);
    seq = rev;
    int k = 0;

    Node * temp = NULL;
    Node * curr = NULL;

    //Will make  a sequence of linked lists containing all the elements
    while(rev != NULL) //shell sort loop
    {
       k = rev->value;
       List * Newlist = CreateList(k);
	
       List * new = Newlist;
       temp = head;//set temp to head of linked list
       while(temp != NULL)
       {
         curr = temp->next;//pointer to next node on list
         temp -> next = new->node;
         new->node =  temp;
         new = new ->next;//update sequence of linked lists
         if(new == NULL)
         {
            new = Newlist;//set back to the beginning
         }
         temp = curr;//move to next node
       }    
       
       //sort the above iteration of a shell
     
       new = Newlist;
       while(new != NULL)
       {
         new->node = reverse_list(new->node);
         new->node = LastSort(new->node);
         new = new -> next;
       }
    	
       // Combine the separated lists into the original one and repeat for a 
       // different value from the shell sort sequence 
       //currently temp points to null
       
       new = Newlist;
       List * iterlist = new;
       head = new-> node; //first value of temp
       while(new -> node != NULL)
       {
         temp = new -> node;//set temp to point at first node
         new -> node = temp -> next;//need to move onto next node 
         iterlist = iterlist -> next;//update to next linked list on sequence
         if(iterlist == NULL)
         {
           iterlist = Newlist;
         }
         temp -> next =  iterlist -> node;//next value of temp
         new = iterlist;//update new to nexton sequence
       }   
       rev = rev-> next;//move to next shell
	
       destroy_list(Newlist);  //delete this sequence
   }   
        
   //destroy_node(seq);
   destroy_node(seq);
   return head;
}


Node * Load_From_File(char * Filename)
{
   FILE * ptr = NULL;
   Node * head = NULL;
   Node * tail = NULL;
   ptr = fopen(Filename,"rb");
	int x = 0;
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
	x++;
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

