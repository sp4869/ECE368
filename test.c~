#include <stdlib.h>

#include <stdio.h>
#include<string.h>


int main(int argc,char ** argv)
{ 
 int i = 0;
 int a = 0;
 int j = 0;
 int Array[20] = {3,7,9,0,5,1,6,8,4,2,0,6,1,5,7,3,4,9,8,2};
 int temp = 0;
 int swaps = 0;
 int k = 0;
 int subarray[2] = {13,4};
 for(k = 0;a < 2;a++)
  {
     k = subarray[a];
     
     for (j = 0;j < 20; j++)
     {
        for (i = j + k;i < 20;i = i + k)
          {
             if (Array[i - k] > Array[i]) 
              {
                 temp = Array[i];
                 Array[i] = Array[i - k];
                 Array[i - k] = temp;
                 swaps++;
               } 
              else
               {
                 break;
               }
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
