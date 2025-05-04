#include <stddef.h>

typedef struct {
  size_t total_size;
  char *pointer;
  size_t current;
} LinearAllocator;

void AllocInit(LinearAllocator *alloc, size_t size);

void *Allocate(LinearAllocator *alloc, size_t size);

void Free(LinearAllocator *alloc);
