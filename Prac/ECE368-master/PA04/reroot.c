#include "reroot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * * argv){

	Node * node = load_file(argv[1]);

	pack(node);

	Stack * stack = NULL;
	clock_t start_time_reroot = clock();
	stack = reroot(stack, node, node->left, node->left->left);
	stack = reroot(stack, node, node->left, node->left->right);
	stack = reroot(stack, node, node->right, node->right->left);
	stack = reroot(stack, node, node->right, node->right->right);
	clock_t end_time_reroot = clock();

	
	clock_t start_time = clock();
	Node * smallest = create_node(node->cutline, node->width, node->height);
	smallest->area = smallest->width * smallest->height;
	while(stack != NULL){
		Node * temp = stack->node;
		stack = stackPop(stack);

		double area = temp->width * temp->height;
		if(smallest->area > area){
			smallest->area = area;
			smallest->width = temp->width;
			smallest->height = temp->height;
		}

		free(temp);
	}
	clock_t end_time = clock();

	print_screen_dump(node, smallest, (double)(end_time-start_time)/CLOCKS_PER_SEC,(double)(end_time_reroot-start_time_reroot)/CLOCKS_PER_SEC);

	free(smallest);

	save_file(argv[2], node);
	destroy_node(node);
	return EXIT_SUCCESS;
}

Stack * reroot(Stack * stack, Node * head, Node * edgeNode1, Node * edgeNode2){
	if(head == NULL || edgeNode1 == NULL || edgeNode2 == NULL){
		return stack;
	}

	char headCutline = head->cutline;
	char edge1Cutline = edgeNode1->cutline;


	Node * child = head->left;
	if(child == edgeNode1){
		child = head->right;
	}

	Node * grandChildOnEdge = edgeNode1->left;
	Node * grandChildNotOnEdge = edgeNode1->right;

	if(grandChildOnEdge != edgeNode2){
		grandChildOnEdge = edgeNode1->right;
		grandChildNotOnEdge = edgeNode1->left;
	}

	Node * tempChild = rerootHelper(headCutline, child, grandChildNotOnEdge);
	Node * tempNode = rerootHelper(edge1Cutline, tempChild, grandChildOnEdge);


	stack = reroot(stack, tempNode, grandChildOnEdge, grandChildOnEdge->left);
	stack = reroot(stack, tempNode, grandChildOnEdge, grandChildOnEdge->right);


	stack = stackPush(stack, tempNode);

	free(tempChild);
	return stack;
}

Node * rerootHelper(char cutline, Node * left, Node * right){
	Node * node = create_node(cutline, 0, 0);
	node->left = left;
	node->right = right;
	if( cutline == 'V' ){
		node -> width = (left -> width) + (right -> width);
		node -> height = max(left -> height, right -> height);
	} else if( cutline == 'H'){
		node -> width = max(left -> width, right -> width);
		node -> height = (left -> height) + (right -> height);
	}
	return node;
}

int max(int a, int b){
	if( a > b ){
		return a;
	}
	return b;
}


void pack(Node * node){
	if(node == NULL || node -> left == NULL || node -> right == NULL){
		return;
	}

	Node * left = node -> left;
	Node * right = node -> right;

	pack(left);
	pack(right);

	if( node->cutline == 'V' ){
		node -> width = (left -> width) + (right -> width);
		node -> height = max(left -> height, right -> height);
		update_xcoord(right, left->width);
	} else if( node->cutline == 'H'){
		node -> width = max(left -> width, right -> width);
		node -> height = (left -> height) + (right -> height);
		update_ycoord(left, right -> height);
	}

}

void update_ycoord(Node * node, int coord){
	if(node == NULL){
		return;
	}
	node -> ycoord += coord;
	update_ycoord(node -> left, coord);
	update_ycoord(node -> right, coord);
}

void update_xcoord(Node * node, int coord){
	if(node == NULL){
		return;
	}
	node -> xcoord += coord;
	update_xcoord(node -> left, coord);
	update_xcoord(node -> right, coord);
}

void destroy_node(Node * node){
	if(node->left != NULL){
		destroy_node(node->left);
	}

	if(node->right != NULL){
		destroy_node(node->right);
	}

	free(node);
}


Node * create_node(char cutline, double width, double height){
	Node * node = malloc(sizeof(Node));
	node -> left = NULL;
	node -> right = NULL;
	node -> cutline = cutline;
	node -> width = width;
	node -> height = height;
	node -> xcoord = 0;
	node -> ycoord = 0;
	return node;
}



Node * load_file(char * file_name){
    FILE * file = fopen(file_name, "r");

    if(file == NULL){
        return NULL;
    }
	unsigned char temp;
	double width, height;

	Stack * stack = NULL;

	while(fscanf(file, "%c", &temp) > 0){

		if(temp == '('){
			width = 0;
			height = 0;

			fscanf(file, "%lf,%lf", &width, &height);

			fscanf(file, "%c", &temp);

			Node * node = create_node('-', width, height);
			stack = stackPush(stack, node);

		} else{

			Node * right = stack -> node;
			stack = stackPop(stack);
			Node * left = stack -> node;
			stack = stackPop(stack);

			Node * node = create_node(temp, 0, 0);
			node -> left = left;
			node -> right = right;
			stack = stackPush(stack, node);
		}

	}

	Node * head = stack->node;
	stackPop(stack);

	fclose(file);
	return head;
}

void pre_order(Node * head){
	if(head == NULL){
		return;
	}
	if(head -> cutline == '-'){
		printf("(%e,%e)", head->width, head->height);
	} else{
		printf("%c", head->cutline);
	}
	pre_order(head->left);
	pre_order(head->right);
}

void in_order(Node * head){
	if(head == NULL){
		return;
	}
	in_order(head->left);
	if(head -> cutline == '-'){
		printf("(%e,%e)", head->width, head->height);
	} else{
		printf("%c", head->cutline);
	}
	in_order(head->right);
}
void post_order(Node * head){
	if(head == NULL){
		return;
	}
	post_order(head->left);
	post_order(head->right);
	if(head -> cutline == '-'){
		printf("(%e,%e)", head->width, head->height);
	} else{
		printf("%c", head->cutline);
	}
}
void print_screen_dump(Node * head, Node * smallest, double elapsed_time, double elapsed_time_reroot){
	printf("\nPreorder : ");
	pre_order(head);
	printf("\n\nInorder : ");
	in_order(head);
	printf("\n\nPostorder : ");
	post_order(head);

	Node * coordNode = head;
	Node * beforeCoordNode = head;
	while(coordNode != NULL){
		beforeCoordNode = coordNode;
		coordNode = coordNode -> left;
	}

	printf("\n\n");
	printf("Width: %e\n", head->width);
	printf("Height: %e\n\n", head->height);
	printf("X-coordinate: %e\n", beforeCoordNode->xcoord);
	printf("Y-coordinate: %e\n\n", beforeCoordNode->ycoord);
	printf("Elapsed time: %e\n\n", elapsed_time);
	printf("Best width: %e\n", smallest->width);
	printf("Best height: %e\n\n", smallest->height);
	printf("Elapsed time for re-rooting: %e\n\n", elapsed_time_reroot);
}

void print_post_order(FILE * file, Node * node){
	if(node == NULL){
		return;
	}
	print_post_order(file, node->left);
	print_post_order(file, node->right);
	if(node->cutline == '-'){
		fprintf(file, "%e %e %e %e\n", node->width, node->height, node->xcoord, node->ycoord);
	}
}

int save_file(char * file_name, Node * head){
	FILE * file = fopen(file_name, "w");
	if(file == NULL){
		return -1;
	}
	
	print_post_order(file, head);

	fclose(file);
	return 0;
}



Stack * stackPush(Stack * stack, Node * node){
	Stack * newStack = malloc(sizeof(Stack));
	newStack -> node = node;
	newStack -> next = stack;
	return newStack;
}


Stack * stackPop(Stack * stack){
	if(stack == NULL){
		return NULL;
	}
	Stack * next = stack -> next;
	free(stack);
	return next;
}
