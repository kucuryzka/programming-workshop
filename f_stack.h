typedef struct {
  int *data;
  int top;
  int capacity;
} stack;

void init_stack(stack *stakk);
int is_empty(stack *stakk);
void push(stack *stakk, int value, int *flag);
int pop(stack *stakk, int *flag);

#define SUCCES 1
#define FAIL 0
