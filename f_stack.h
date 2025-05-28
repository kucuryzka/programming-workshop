typedef struct {
  int *data;
  int top;
  int capacity;
} stack_t;

void init_stack(stack_t *stack);
int is_empty(stack_t *stack);
int push(stack_t *stack, int value);
int pop(stack_t *stack, int *elem);

#define SUCCES 1
#define FAIL 0
