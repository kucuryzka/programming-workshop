#include "linear_allocator.h"
#include <stddef.h>
#include <stdlib.h>

void AllocInit(LinearAllocator *alloc, size_t size) {
  alloc->pointer = malloc(size);

  alloc->total_size = size;
  alloc->current = 0;
}

void *Allocate(LinearAllocator *alloc, size_t size) {
  if (alloc->current + size > alloc->total_size)
    return NULL;

  void *pointer = alloc->pointer + alloc->current;
  alloc->current += size;

  return pointer;
}

void Free(LinearAllocator *alloc) {
  free(alloc->pointer);

  alloc->pointer = NULL;
  alloc->total_size = 0;
  alloc->current = 0;
}