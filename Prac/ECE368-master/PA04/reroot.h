typedef struct _node {
	int node_no;
	struct _node * left;
	struct _node * right;
	char cutline;
	double width;
	double height;
	double xcoord;
	double ycoord;
	double area;
} Node;

Node * create_node(char cutline, double width, double height);
Node * load_file(char * file_name);

typedef struct _stack {
    struct _stack * next;
    Node * node;
} Stack;
Stack * stackPush(Stack * stack, Node * node);
Stack * stackPop(Stack * stack);
void destroy_node(Node * head);
void pack(Node * node);
void update_ycoord(Node * node, int coord);
void update_xcoord(Node * node, int coord);
int max(int a, int b);
Stack * reroot(Stack * stack, Node * head, Node * edgeNode1, Node * edgeNode2);
Node * rerootHelper(char cutline, Node * left, Node * right);

void print_screen_dump(Node * head, Node * smallest, double elapsed_time, double elapsed_time_reroot);

void pre_order(Node * head);
void in_order(Node * head);
void post_order(Node * head);

int save_file(char * file_name, Node * head);

