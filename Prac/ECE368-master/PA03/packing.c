#include "packing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * * argv){

	Node_Info_Overall * info = load_file(argv[1]);

	clock_t start_time = clock();
	Node * head = build_node(info->nodes_info, info->node_count-1);
	pack(head);
	update_coord(info, head);
	clock_t end_time = clock();

	print_screen_dump(info, head, (double)(end_time-start_time)/CLOCKS_PER_SEC);
	save_file(argv[2], info);

	destroy_node(head);
	free(info->nodes_info);
	free(info);

	return EXIT_SUCCESS;
}

void pre_order(Node * head){
	if(head == NULL){
		return;
	}
	printf("%d ", head->node_no);
	pre_order(head->left);
	pre_order(head->right);
}

void in_order(Node * head){
	if(head == NULL){
		return;
	}
	in_order(head->left);
	printf("%d ", head->node_no);
	in_order(head->right);
}
void post_order(Node * head){
	if(head == NULL){
		return;
	}
	post_order(head->left);
	post_order(head->right);
	printf("%d ", head->node_no);
}
void print_screen_dump(Node_Info_Overall * info, Node * head, double elapsed_time){
	printf("\nPreorder : ");
	pre_order(head);
	printf("\n\nInorder : ");
	in_order(head);
	printf("\n\nPostorder : ");
	post_order(head);
	printf("\n\n");
	printf("Width: %e\n", head->width);
	printf("Height: %e\n\n", head->height);
	printf("X-coordinate: %e\n", info->nodes_info[info->block_count-1].xcoord);
	printf("Y-coordinate: %e\n\n", info->nodes_info[info->block_count-1].ycoord);
	printf("Elapsed Time: %e\n\n", elapsed_time);
}


void update_coord(Node_Info_Overall * info, Node * node){
	if(node == NULL){
		return;
	}

	if(node -> left == NULL && node -> right == NULL){
		info -> nodes_info[node->node_no-1].xcoord = node -> xcoord;
		info -> nodes_info[node->node_no-1].ycoord = node -> ycoord;
	} else{
		update_coord(info, node -> left);
		update_coord(info, node -> right);
	}
}

int save_file(char * file_name, Node_Info_Overall * info){
	FILE * file = fopen(file_name, "w");
	if(file == NULL){
		return 0;
	}
	int written = 0;
	

	int i;
	written += fprintf(file, "%d\n", info->block_count);
	for(i=0; i < (info->block_count); i++){
		Node_Info node_info = info->nodes_info[i];
		written += fprintf(file, "%d %e %e %e %e\n", node_info.node_no, node_info.width, node_info.height, node_info.xcoord, node_info.ycoord);
	}
	fclose(file);
	return written;
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


Node_Info_Overall * load_file(char * file_name){
    FILE * file = fopen(file_name, "r");
    if(file == NULL){
        return NULL;
    }

	Node_Info_Overall * info = malloc(sizeof(Node_Info_Overall));

	int temp, i;

	if( fscanf(file, "%d", &temp) < 1){
		return NULL;
	}
	info->block_count = temp;

	if( fscanf(file, "%d", &temp) < 1){
		return NULL;
	}
	info->node_count = temp;

	Node_Info * nodes_info = malloc( info->node_count * sizeof(Node_Info));
	
	for(i=0; i < (info->block_count); i++){
		fscanf(file, "%d %d %d %d %c %lf %lf", &nodes_info[i].node_no, &nodes_info[i].parent_no, &nodes_info[i].left_no, &nodes_info[i].right_no, &nodes_info[i].cutline, &nodes_info[i].width, &nodes_info[i].height );
	}
	
	for(;i < (info->node_count); i++){
		fscanf(file, "%d %d %d %d %c", &nodes_info[i].node_no, &nodes_info[i].parent_no, &nodes_info[i].left_no, &nodes_info[i].right_no, &nodes_info[i].cutline );
		fseek(file, 4, SEEK_CUR);
	}

	info -> nodes_info = nodes_info;
	fclose(file);
	return info;
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

Node * build_node(Node_Info * nodes_info, int i ){
	Node_Info node_info = nodes_info[i];
	Node * node = create_node(node_info.node_no, node_info.cutline, node_info.width, node_info.height);
	if(node_info.left_no > -1){
		node -> left = build_node( nodes_info, node_info.left_no-1 );
	}
	if(node_info.right_no > -1){
		node -> right = build_node( nodes_info, node_info.right_no-1 );
	}
	return node;
}



Node * create_node(int node_no, char cutline, double width, double height){
	Node * node = malloc(sizeof(Node));
	node -> node_no = node_no;
	node -> left = NULL;
	node -> right = NULL;
	node -> cutline = cutline;
	node -> width = width;
	node -> height = height;
	node -> xcoord = 0;
	node -> ycoord = 0;
	return node;
}

