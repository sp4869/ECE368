#include <stdlib.h>

#include <stdio.h>
#include<string.h>


int main(int argc,char ** argv)
{ 
 int i = 0;
 //int a = 0;
 int j = 0;
 int Array[20] = {3,7,9,0,5,1,6,8,4,2,0,6,1,5,7,3,4,9,8,2};
 int temp = 0;
 int swaps = 0;
 for (j = 1;j < 20; j++)
     {
        for (i = j;i > 0;i--)
          {
             if (Array[i - 1] > Array[i]) 
              {
                 temp = Array[i];
                 Array[i] = Array[i - 1];
                 Array[i - 1] = temp;
                 swaps++;
               } 
              else
               {
                 break;
               }
          }
       }
  for(i = 0;i < 20;i++)
    {
      printf("%d\n",Array[i]);
    }
   printf("%d\n",swaps); 
   return EXIT_SUCCESS;
}
