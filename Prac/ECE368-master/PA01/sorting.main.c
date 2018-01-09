#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * * argv){
	if(argc != 5){
		printf("[ERROR] The number of input arguments should be four.\n");
		return EXIT_FAILURE;
	}

	int size = 0;
	clock_t io_start_time = clock();
	long * array = Load_File(argv[2], &size);
	clock_t io_end_time = clock();
	
	double n_comp = 0;
	double n_move = 0;
	
	io_start_time += clock();
	Print_Seq(argv[3], size);
	io_end_time += clock();

	clock_t sort_start_time = clock();
	if(argv[1][0] == 's'){
		Shell_Selection_Sort(array, size, &n_comp, &n_move);
	} else{
		Shell_Insertion_Sort(array, size, &n_comp, &n_move);
	}
	clock_t sort_end_time = clock();


	io_start_time += clock();
	int written = Save_File(argv[4], array, size);
	io_end_time += clock();
	if(written != size){
		printf("[ERROR] error occurred while saving file\n");
		return EXIT_FAILURE;
	}

	printf("\n");
	printf("Number of comparisons:\t%le times\n", n_comp);
	printf("Number of moves:\t%le times\n", n_move);
	printf("I/O time:\t\t%le sec\n", (double)(io_end_time-io_start_time)/CLOCKS_PER_SEC);
	printf("Sorting time:\t\t%le sec\n", (double)(sort_end_time-sort_start_time)/CLOCKS_PER_SEC);
	printf("\n");
	
	if(array != NULL){
		free(array);
	}

	return EXIT_SUCCESS;
}
