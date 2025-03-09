typedef struct {
  int *data;
  int top;
  int capacity;
} stack;

void init_stack(stack *stakk);
int is_empty(stack *stakk);
void push(stack *stakk, int value);
int pop(stack *stakk);
void print_stack(stack *stakk);
