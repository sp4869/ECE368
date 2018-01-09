#include "river.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXIMUM_INT 2147483647
#define MINIMUM_INT -2147483648

int main(int argc, char * * argv){
	int n, vertex_n;
	int ** boards = load_file(argv[1], &n);
	
	
	Vertex ** vertices = create_vertices(boards, n, &vertex_n);
//	print_vertex(vertices, vertex_n);
	connect_vertices(vertices, vertex_n);

	dijkstra(vertices, vertex_n, 0);

	printf("%d\n", vertices[vertex_n-1]->d - 1);

	
	destroy_vertex(vertices, vertex_n);
//	print_board(boards, n);
	destroy_board(boards, n);
	return EXIT_SUCCESS;
}

void dijkstra( Vertex ** vertices, int vertex_n, int start_idx ){
	Vertex ** p_queue = build_heap(vertices, vertex_n);
	int p_queue_n = vertex_n;
	int i;
	for(i=0; i<vertex_n; i++){
		p_queue[i]->d = MAXIMUM_INT;
		p_queue[i]->pred_no = -1;
	}

	p_queue[start_idx]->d = 0;

	while(p_queue_n > 0){
//		print_p_queue(p_queue, p_queue_n);
		Vertex * u = extract_min(p_queue, &p_queue_n);
		Edge * edge = u -> edge;

		while(edge != NULL){
			int v_idx = index_of(p_queue, p_queue_n, edge->vertex_no);
			
			if( v_idx > -1 && (p_queue[v_idx]->d) > (u->d + edge->weight)  ){
				p_queue[v_idx] -> d = u->d + edge->weight;
				p_queue[v_idx] -> pred_no = u->vertex_no;
			}
			
			edge = edge->next;
		}
		downward_heapify(p_queue, 0, p_queue_n);

	}
	
//	print_vertex(vertices, vertex_n);
	
	free(p_queue);
	
}

void print_p_queue(Vertex ** p_queue, int p_queue_n){
	int i;
	printf("p_queue_n : %d\n", p_queue_n);
	printf("< ");
	for(i=0; i<p_queue_n; i++){
		printf("%d ", p_queue[i]->vertex_no );
	}
	printf(">\n");
}

int index_of( Vertex ** p_queue, int p_queue_n, int vertex_no ){
	int i;
	for(i=0; i<p_queue_n; i++){
		if(p_queue[i]->vertex_no == vertex_no){
			return i;
		}
	}
	return -1;
}

Vertex * extract_min(Vertex ** p_queue, int * p_queue_n ){
	if( *p_queue_n <= 0 ){
		return NULL;
	}
	Vertex * temp = p_queue[0];
	p_queue[0] = p_queue[*p_queue_n-1];
	p_queue[*p_queue_n-1] = temp;
	(*p_queue_n)--;
	return temp;
}

Vertex ** build_heap(Vertex ** vertices, int vertex_n){
	int i;
	Vertex ** vertices_dup = malloc( vertex_n * sizeof(Vertex));
	for(i=0; i<vertex_n; i++){
		vertices_dup[i] = vertices[i];
	}
	return vertices_dup;
}

void downward_heapify(Vertex ** vertices, int i, int n){
	Vertex * temp = vertices[i];
	int j;
	while( (j = 2 * i + 1) < n ){
		if(j < n-1 && vertices[j]->d > vertices[j+1]->d){
			j++;
		}
		if( temp->d <= vertices[j]->d ){
			break;
		} else{
			vertices[i] = vertices[j];
			i = j;
		}
	}
	vertices[i] = temp;
}

void connect_vertices(Vertex ** vertices, int vertex_n){
	int i,j;
	int m,n;
	for(i=0; i<vertex_n; i++){
		Vertex * src = vertices[i];
		for(j=0; j<vertex_n; j++){
			if(i == j){
				continue;
			}
			Vertex * dest = vertices[j];
			int weight;
			
			if( src->col == dest->col ){
				Vertex * higher;
				Vertex * lower;
				if( src->start_row < dest->start_row ){
					higher = src;
					lower = dest;
				} else{
					higher = dest;
					lower = src;
				}
				weight = 2 * ((lower -> start_row) - (higher -> end_row) - 1);
			} else{
				int is_horizontal = 0;
				if( (src->start_row) == (dest->start_row) ){
					is_horizontal = 1;
				} else if( (src->start_row) > (dest->start_row) ){
					if( (src->start_row) <= (dest->end_row)){
						is_horizontal = 1;
					}
				} else{
					if( (dest->start_row) <= (src->end_row)){
						is_horizontal = 1;
					}
				}

				if(is_horizontal){
					weight = 2 * (abs((dest->col) - (src->col)) - 1) + 1;
				} else{
					Vertex * higher;
					Vertex * lower;
					if( (src -> start_row)  >  (dest -> start_row) ){
						higher = dest;
						lower = src;
					} else{
						higher = src;
						lower = dest;
					}

					m = (lower->start_row)  - (higher->end_row);
					n = abs( (dest->col) - (src->col) );
					if( m > n ){
						weight = 2 * ((lower -> start_row) - (higher -> end_row) - 1);
					} else{
						weight = 2 * (abs((dest->col) - (src->col)) - 1) + 1;
					}
				}

			}

			if(src -> edge == NULL){
				src -> edge = create_edge(j, weight);
			} else{
				Edge * edge = src -> edge;
				while( edge -> next != NULL ){
					edge = edge -> next;
				}
				edge -> next = create_edge(j, weight);
			}
			
		}
	}
}

Edge * create_edge(int vertex_no, int weight){
	Edge * edge = malloc(sizeof(Edge));
	edge -> vertex_no= vertex_no;
	edge -> weight = weight;
	edge -> next = NULL;
	return edge;
}

void print_vertex(Vertex ** vertices, int vertex_n){
	int i;
	for(i=0; i<vertex_n; i++){
		printf("vertex[%d] : vertex_no = %d, col = %d, start_row = %d, end_row = %d, d = %d, pred_no = %d\n", i, vertices[i]->vertex_no, vertices[i]->col, vertices[i]->start_row, vertices[i]->end_row, vertices[i]->d, vertices[i]->pred_no);
	}
}

void destroy_vertex(Vertex ** vertices, int vertex_n){
	if(vertices == NULL){
		return;
	}
	int i;
	for(i=0; i<vertex_n; i++){
		if(vertices[i] != NULL){
			destroy_edge(vertices[i] -> edge);
			free(vertices[i]);
		}
	}
	free(vertices);
}

void destroy_edge(Edge * edge){
	if(edge == NULL){
		return;
	}
	destroy_edge(edge -> next);
	free(edge);
}

Vertex ** create_vertices(int ** boards, int n, int * vertex_n){
	int j, i;
	int vertex_no = 0;
	*vertex_n = 2;

	Stack * stack = NULL;
// compute vertex_n;
    for(j=0; j<n; j++){
        for(i=0; i<n-1; i++){
            if(boards[i][j] == '0' && stack != NULL){
                while(stack != NULL){
                    stack = stackPop(stack);
                }
                (*vertex_n)++;

            } else if(boards[i][j] == '1'){
                stack = stackPush(stack, i);
            }

        }

    }
	if(stack != NULL){
		(*vertex_n)++;
	}
	while(stack != NULL){
		stack = stackPop(stack);
	}


	
// create Vertices

	Vertex ** vertices = malloc( *vertex_n * sizeof(Vertex));
	vertices[0] = create_vertex( vertex_no, 0, 0, n-2);
	vertex_no++;
	int k = 1;

	for(j=0; j<n; j++){
		for(i=0; i<n-1; i++){
			if(boards[i][j] == '0' && stack != NULL){
				int min = MAXIMUM_INT;
				int max = MINIMUM_INT;
				while(stack != NULL){
					if( stack -> n > max ){
						max = stack -> n;
					}
					if( stack -> n < min ){
						min = stack -> n;
					}
					stack = stackPop(stack);
				}
				if( i == 0 ){
					vertices[k++] = create_vertex(vertex_no, j, min, max);
					vertex_no++;
				} else{
					vertices[k++] = create_vertex(vertex_no, j+1, min, max);
					vertex_no++;
				}
			//	printf("[create vertex] col = %d, start = %d, end = %d\n", j, min, max);
				
			} else if(boards[i][j] == '1'){
				stack = stackPush(stack, i);
			}

		}

	}

	if(stack != NULL){
		int min = MAXIMUM_INT;
		int max = MINIMUM_INT;
		while(stack != NULL){
			if( stack -> n > max ){
				max = stack -> n;
			}
			if( stack -> n < min ){
				min = stack -> n;
			}
			stack = stackPop(stack);
		}
		vertices[k++] = create_vertex(vertex_no, j, min, max);
		vertex_no++;
//		printf("[create vertex] col = %d, start = %d, end = %d\n", j+1, min, max);

	}
	vertices[k] = create_vertex(vertex_no, j+1, 0, n-2);
	vertex_no++;
	return vertices;
}

Vertex * create_vertex(int vertex_no, int col, int start_row, int end_row){
	Vertex * vertex = malloc(sizeof(Vertex));
	vertex -> vertex_no = vertex_no;
	vertex -> col = col;
	vertex -> start_row = start_row;
	vertex -> end_row = end_row;
	vertex -> edge = NULL;
	vertex -> d = MAXIMUM_INT;
	vertex -> pred_no = -1;
	return vertex;
}

int ** load_file(char * file_name, int * n){
    FILE * file = fopen(file_name, "r");

    if(file == NULL){
        return NULL;
    }

	fscanf(file, "%d\n", n);

	int i, j, num = *n;
	unsigned char temp;

	int ** boards = malloc( num * (num-1) * sizeof(int));

	for(i=0; i<num-1; i++){
		int * row = malloc(num * sizeof(int));
		j=0;
		while(1){
			temp = fgetc(file);

			if(temp == '\n'){
				break;
			} else if(temp == '0' || temp == '1'){
				row[j] = temp;
			}
			j++;
		}

		boards[i] = row;
	}

	fclose(file);
	return boards;
}

void print_board(int ** boards, int n){
	int i,j;

	printf("\n");
	for(i=0; i<n-1; i++){
		for(j=0; j<n; j++){
			printf("%c\t", boards[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

void destroy_board(int ** boards, int n){
	if(boards == NULL){
		return;
	}
	int i;
	for(i=0; i<n-1; i++){
		if(boards[i] != NULL){
			free(boards[i]);
		}
	}
	free(boards);
}

Stack * stackPush(Stack * stack, int n){
    Stack * newStack = malloc(sizeof(Stack));
    newStack -> n = n;
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

int abs(int a){
	if(a < 0){
		return a * -1;
	}
	return a;
}

