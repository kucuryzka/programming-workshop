typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct {
  node *head;
  node *tail;
  int size;
} linked_list;

void init_list(linked_list *list);
void add_to_head(linked_list *list, int value);
void add_to_tail(linked_list *list, int value);
void add_to_middle(linked_list *list, int position, int value);
void remove_element(linked_list *list, int position);
int find_element(linked_list *list, int position);
int count_elements(linked_list *list);
void print_list(linked_list *list);
