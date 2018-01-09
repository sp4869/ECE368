#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

void swap(long * a, long * b){
	long temp = *a;
	*a = *b;
	*b = temp;
}

Node * reverse_node(Node * head){
	Node node;
	node.next = NULL;
	while(head != NULL){
		Node * nextNode = head -> next;
		head -> next = node.next;
		node.next = head;
		head = nextNode;
    }
	head = node.next;

	return head;
}

Node * create_node(long value){
	Node * node = malloc(sizeof(Node));
	node -> value = value;
	node -> next = NULL;
	return node;
}

void destroy_node(Node * node){
	if(node == NULL){
		return;
	}
	destroy_node( node -> next );
	free(node);
}

List * create_lists(int k){
	List * headList = NULL;
	int i;
	for(i=0; i<k; i++){
		List * list = malloc(sizeof(List));
		list->node = NULL;
		list->next = headList;
		headList = list;
	};
	return headList;
}

void destroy_lists(List * list){
	if(list == NULL){
		return;
	}
	destroy_lists(list->next);
	free(list);
}

Node * Load_File(char *Filename){
	FILE * file = fopen(Filename, "r");
	if(file == NULL){
		return NULL;
	}

	long temp = 0;
	int count = 0;

	Node * head = NULL;
	Node * tail = NULL;
//	int i=0;
//
	while( fscanf(file, "%lu", &temp) > 0 ){
		Node * node = create_node(temp);
		count++;
		if(tail == NULL){
			head = tail = node;
		} else{
			tail -> next = node;
			tail = node;
		}
		
    }

	fclose(file);
	return head;
}



int Save_File(char *Filename, Node * list){
	FILE * file = fopen(Filename, "w");
	if(file == NULL){
		return -1;
	}

	int written=0, temp=0;
	while(list != NULL){
		temp = fprintf(file, "%lu\n", list -> value);
		if(temp > -1){
			written++;
		}
		list = list -> next;
	}

	fclose(file);
	return written;
}

Node * insertion_sort_helper(Node * head, Node * current){
	if( head == NULL ){
		return current;
	}
	if( (head->value) < (current->value) ){
		current -> next = head;
		return current;
	}

	head -> next = insertion_sort_helper(head -> next, current);
	return head;
}

Node * insertion_sort(Node * head){
	Node * newList = NULL;
	while(head != NULL){
		Node * nextNode = head -> next;
		head -> next = NULL;
		newList = insertion_sort_helper(newList, head);
		head = nextNode;
	}
	return newList;
}

Node * Shell_Sort(Node * node){
	// initialize
	int i, k, count=0, seqCount=0;
	
	// generate sequence
	Node * temp = node;
	while(temp != NULL){
		count++;
		temp = temp -> next;
	}

	int * seqArray = Generate_Seq(count, &seqCount);

	// shell sort
	for(i=seqCount-1; i>=0; i--){
		k=seqArray[i];


		List * headList = create_lists(k);

		// distribute nodes into k lists
		List * list = headList;
		temp = node;
		while(temp != NULL){
			Node * nextNode = temp -> next;
			temp -> next = list->node;
			list->node = temp;
			temp = nextNode;
			list = list->next;
			if(list == NULL){
				list = headList;
			}
		}

		// sort nodes of each list
		list = headList;
		while(list != NULL){
			list->node = insertion_sort(list->node);
			list = list->next;
		}
	
		// merge nodes into one linked list
		list = headList;
		List * nextList;
		node = headList->node;
		while( list -> node != NULL){
			temp = list->node;
			list -> node = temp -> next;
	
			nextList = list -> next;
			if(nextList == NULL){
				nextList = headList;
			}
			
			temp -> next = nextList -> node;
			list = nextList;
		}

		destroy_lists(headList);

	}

	free(seqArray);
	return node;
}


int * Generate_Seq(int Size, int * seqCount){
	int depth = 1;
	int seq = 1;
	while(Size > seq){
		seq *= 3;
		depth++;
	}

	int * seqArray = malloc(sizeof(int) * (depth * (depth+1) / 2));

	int first_seq_of_row = 1;
	int i, j;
	int count = 0;

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
			seqArray[count] = seq;
			count++;
		}
		first_seq_of_row *= 2;
	}
	*seqCount = count;
	return seqArray;
}

