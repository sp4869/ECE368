typedef struct _node_info {
	int node_no;
	int parent_no;
	int left_no;
	int right_no;
	char cutline;
	double width;
	double height;
	double xcoord;
	double ycoord;
} Node_Info;

typedef struct _node_info_overall {
	int node_count;
	int block_count;
	Node_Info * nodes_info;
} Node_Info_Overall;

typedef struct _node {
	int node_no;
	struct _node * left;
	struct _node * right;
	char cutline;
	double width;
	double height;
	double xcoord;
	double ycoord;
} Node;


void update_coord(Node_Info_Overall * info, Node * node);

Node_Info_Overall * load_file(char * file_name);

Node * create_node(int node_no, char cutline, double width, double height);

Node * build_node(Node_Info * nodes_info, int i);

void destroy_node(Node * head);

void pack(Node * node);

int max(int a, int b);

void update_ycoord(Node * node, int coord);

void update_xcoord(Node * node, int coord);

void print_screen_dump(Node_Info_Overall * info, Node * head, double elapsed_time);

void pre_order(Node * head);
void in_order(Node * head);
void post_order(Node * head);

int save_file(char * file_name, Node_Info_Overall * info);

