#include <stdlib.h>
#include "sorting.h"
#include <stdio.h>
#include<string.h>
#include<time.h>
long * GenSeq(int,long*);
long power(long,long);
int main(int argc,char * argv[])
{
  clock_t startIO;//starts recording runnning time of program
  clock_t stopIO;//stops recording running time of program
  clock_t startSort;//starts recording time to sort
  clock_t stopSort;//stops recording time to sort

  int i = 0;//
  int size = 0 ;//Size of unsorted array
 
  double comp = 0;//Number of Comparisons
  double moves = 0;//Number of Moves
  startIO = clock();//starts the clockIO
 
  long * newfile = Load_From_File(argv[2],&size);//Loads the file
 
  startSort = clock();//starts clock for sort
  if(argv[1] && strcmp(argv[1],"i") == 0)
  {
    Shell_Insertion_Sort(newfile,size,&comp,&moves);//Calls Insertion sort
  } 
  else if(argv[1] && strcmp(argv[1],"s") == 0)
   { 
     Shell_Selection_Sort(newfile,size,&comp,&moves);//Calls selection sort
   }
  stopSort = clock(); //stops clock for sorting
  
  int sequencePrint = Print_Seq(argv[3],size);//prints sequence 
  int savebinary = 0;
  savebinary = Save_To_File(argv[4],newfile,size);//Saves sorted array in binary file
  for(i = 0; i < size;i++)
  {
     // printf("%lu\n",newfile[i]);
  }  
  if(newfile != NULL)
  {
   free(newfile);
  }

  stopIO = clock();//STops clock for program run time
  
  printf("Number of long integers read: %d\n",size);
  printf("Number of long integers stored: %d\n",size);
  printf("Length of sequence: %d\n",sequencePrint);
  printf("Number of comparisons: %f\n",comp);
  printf("Number of moves: %f\n",moves);
  printf("I/O time: %f\n",((double)(stopIO - startIO)) / CLOCKS_PER_SEC);
  printf("Sorting time: %f\n",((double)(stopSort - startSort)) / CLOCKS_PER_SEC);
  
  return EXIT_SUCCESS;
} 
  
  




 
  


