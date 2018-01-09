#ifndef PA01_H
#define PA01_H
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

long *Load_From_File(char *Filename,int *Size);
int Save_To_File(char *Filename,long *Array,int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
int Print_Seq(char *Filename, int Size);

#endif
