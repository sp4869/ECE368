typedef struct _edge {
	int vertex_no;
	int weight;
	struct _edge * next;
} Edge;
typedef struct _vertex {
	int vertex_no;
	int col;
	int start_row;
	int end_row;
	Edge * edge;
	int d;
	int pred_no;
} Vertex;

typedef struct _stack {
    struct _stack * next;
    int n;
} Stack;

Stack * stackPop(Stack * stack);
Stack * stackPush(Stack * stack, int n);

int ** load_file(char * file_name, int * n);
void print_board(int ** boards, int n);
void destroy_board(int ** boards, int n);
Vertex * create_vertex(int vertex_no, int col, int start_row, int end_row);
void destroy_vertex(Vertex ** vertices, int n);
Vertex ** create_vertices(int ** boards, int n, int * vertex_n);
void print_vertex(Vertex ** vertices, int vertex_n);
void destroy_vertex(Vertex ** vertices, int vertex_n);
void connect_vertices(Vertex ** vertices, int vertex_n);
Edge * create_edge(int vertex_idx, int weight);
void destroy_edge(Edge * edge);
int abs(int a);
void downward_heapify(Vertex ** vertices, int i, int n);
Vertex ** build_heap(Vertex ** vertices, int vertex_n);
void dijkstra(Vertex ** vertices, int vertex_n, int start_idx);
Vertex * extract_min(Vertex ** p_queue, int * p_queue_n );
int index_of( Vertex ** p_queue, int p_queue_n, int vertex_no );
void print_p_queue(Vertex ** p_queue, int p_queue_n);
