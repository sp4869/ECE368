#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

void swap(long * a, long * b){
	long temp = *a;
	*a = *b;
	*b = temp;
}



long * Load_File(char *Filename, int *Size){
	FILE * file = fopen(Filename, "r");
	if(file == NULL){
		return NULL;
	}

	long temp = 0;
	if(fscanf(file, "%lu", &temp) > 0 ){
		*Size = temp;
	}

	long * array = malloc(*Size * sizeof(long));

	int i=0;
	while( fscanf(file, "%lu", &temp) > 0 ){
		array[i] = temp;
		i++;
    }

	fclose(file);
	return array;
}

int Save_File(char *Filename, long *Array, int Size){
	FILE * file = fopen(Filename, "w");
	if(file == NULL){
		return -1;
	}

	int i, written=0, temp=0;
	for(i=0; i<Size; i++){
		temp = fprintf(file, "%lu\n", Array[i]);
		if(temp > -1){
			written++;
		}
	}

	fclose(file);
	return written;
}



void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move){
	if(Size == 1){
		return;
	}

	int i, j, k, l;
	long temp = 0;
	long * seqArray = Generate_Seq(Size);
	int seqSize = (int)seqArray[0];
	for(l=seqSize; l>0; l--){
		k = seqArray[l];
		for(i=k; i<Size; i++){
			temp = Array[i];
			(*N_Move)++;
			j = i;
			(*N_Comp)++;
			while(j >= k && Array[j-k] > temp){
				Array[j] = Array[j-k];
				(*N_Move)++;
				j-=k;
				(*N_Comp)++;
			}
			Array[j] = temp;
			(*N_Move)++;
		}

	}
	free(seqArray);

}

void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move){

	int i, j, min, k, l;
	long * seqArray = Generate_Seq(Size);
	int seqSize = (int)seqArray[0];
	for(l=seqSize; l>0; l--){
		k = seqArray[l];
		for(i=0; i<Size-1; i++){
			min = i;
			for(j=i; j<Size; j=j+k){
				(*N_Comp)++;
				if(Array[j] < Array[min]){
					min = j;
				}
			}
	
			if(min != i){
				swap(&Array[i], &Array[min]);
				*N_Move += 3;
			}
		}
	}
	free(seqArray);

}

long * Generate_Seq(int Size){
	int depth = 1;
	long seq = 1;
	while(Size > seq){
		seq *= 3;
		depth++;
	}

	long * seqArray = malloc(sizeof(long) * (depth * (depth+1) / 2 + 1));

	int first_seq_of_row = 1;
	int i, j;
	long count = 0;

	for(i=0; i<depth; i++){
		for(j=0; j<=i; j++){
			if(j==0){
				seq = first_seq_of_row;
			} else{
				seq = seq * 3 / 2;
			}
			if(seq >= Size){
				break;
			}
			count++;
			seqArray[count] = seq;
		}
		first_seq_of_row *= 2;
	}
	seqArray[0] = count;
	return seqArray;
}

int Print_Seq(char *Filename, int Size){
	long * seqArray = Generate_Seq(Size);
	int count = (int)seqArray[0];
	Save_File(Filename, seqArray, count+1);
	free(seqArray);
	return count;
}
