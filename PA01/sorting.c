#include <stdlib.h>
#include "sorting.h"
#include <stdio.h>
#include<string.h>
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
long * GenSeq(int Size,long * count)
{
  int length = 0;
  int i = 0;
  int j = 0;
  long value = 0;
  long k = 0;
  long * arrayel = malloc(sizeof(long) * Size);
  for (i = 0; i < Size;i++)
  { 
     
     for(j = 0; j <= i; j++)
     {
        value = power(i - j,j);//pow(2,i -j) * pow(3,j)
        if (value < Size)
        {
           arrayel[k] = value;
           length++;
           //printf("%lu\n",arrayel[k]);
           k++;
           *count = length;
        }
        else
        {
           if(power(i + 1, 0) > Size)//pow(2,i +1) * pow(3,0)
              {
                 return arrayel;            // go to the next row calculate first element of the next row
              }
           j = i + 1;
        }  
      }
  }  
  return arrayel;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
    long count = 0;
    long * seq = GenSeq(Size,&count);//generates the sequence
    long i = 0;
    long j = 0;
    long k = 0;
    long temp = 0;
    double moves = 0;
    double comparison = 0;
    for(k = 0; count >= 1 ;count--) //shell sort loop
    {
       k = seq[count - 1];
       for (j = k;j < Size;j++)
       {
           temp = Array[j];
           i = j;
           
           while ((i >= k) && (Array[i - k] > temp)) 
           {
             Array[i] = Array[i-k];//starting the swap
             i = i - k;
             comparison++;//calculates comparisons
           }
           comparison++;
           Array[i] = temp;  
           moves++;//calculates moves
        }
    }
    *N_Move = moves;
    *N_Comp = comparison;
    free(seq);
}

void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
   long min = 0;
  // long l = 0;
   long count = 0;
   long i = 0;
   long temp = 0;//swap variable
   long * seq = GenSeq(Size,&count);
   long k = 0;//subarray loop
   long j = 0;//Change the minimum value
   //long i = 0;//comparison between elements
   double comparison = 0;
   double moves = 0;
   for(k = 0;count >= 1 ;count--)
   {
        k = seq[count - 1];
        for(j = 0; j < Size;j++)
        {
           comparison++;
           min = j; //index of minimum value is set to j
           for(i = j + k;i < Size;i = i + k) 
           {
              comparison++;
              if(Array[min] > Array[i])
              {
                 min = i;   
              }
           }
           if(min != j)
           { 
             temp = Array[j];//Assign value to be swapped to temp
             Array[j] = Array[min];//Swap final and initial values
             Array[min] = temp;//set value
             moves++;
        
           }        
          
        }   
   }
   *N_Move = moves;
   *N_Comp = comparison;
   free(seq);
}

int Print_Seq(char *Filename,int Size)
{
  long i = 0;
  long val = 0;
  long * seq = GenSeq(Size,&val);
  //printf("%lu\n",val);
  FILE * ptr = NULL;
  ptr = fopen(Filename,"w");
  if (ptr == NULL)
  {
    return 0;
  }
  for(i = 0; i < val;i++)
  {
    fprintf(ptr,"%lu\n",seq[i]);
  }
  fclose(ptr);
  free(seq);
  return val;
}
   
long *Load_From_File(char *Filename, int * Size)
{
  FILE * ptr = NULL;
  int count = 0;
  ptr = fopen(Filename,"rb");
  if(ptr == NULL)
  {
    return NULL;
  }
  fseek(ptr,0,SEEK_END);//starts reading to calculate length
  long len = ftell(ptr);
  count = len / sizeof(long);//calculates number of elements
  fseek(ptr,SEEK_SET,0);
  if(ptr == NULL)
  {
    return NULL;
  }
  *Size = count;
  printf("%d\n",count);
  long * storenum = malloc(sizeof(long) * (*Size));  
  fread(storenum,sizeof(long),count,ptr);
  fclose(ptr); 
  return storenum;
}

int Save_To_File(char *Filename, long *Array, int Size)
{
  int i = 0;
  FILE * ptr = NULL;
  ptr = fopen(Filename,"wb");
  if(ptr == NULL)
   {
      return 0;
   }
  //printf("%d",Size);
  for(i = 0; i < Size;i++)
   {
     fwrite(&Array[i],sizeof(long),1,ptr);
   }
  fclose(ptr);
  return i;
}
