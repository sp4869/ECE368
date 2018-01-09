typedef struct _node {
	long value;
	struct _node *next;
} Node;

typedef struct _list {
	Node *node;
	struct _list *next;
} List;

void swap(long * a, long * b);

Node * create_node(long value);
void destroy_node(Node * node);
Node * reverse_node(Node * head);

List * create_lists(int k);
void destroy_lists(List * lists);


Node *Load_File(char *Filename);

int Save_File(char *Filename, Node *list);

Node *Shell_Sort(Node *node);

int Print_Seq(char *Filename, int Size);

int * Generate_Seq(int Size, int * seqCount);
