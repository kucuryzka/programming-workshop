#include <stddef.h>
#include <stdio.h>

typedef struct MemoryBlock {
  struct MemoryBlock *next;
} MemoryBlock;

typedef struct {
  char *memory;
  size_t block_num;
  size_t block_size;
  MemoryBlock *free_block;
  MemoryBlock **block_arr;
} PoolAllocator;

void alloc_init(PoolAllocator *alloc, size_t block_num, size_t block_size);

void *allocate(PoolAllocator *alloc);

void free_alloc(PoolAllocator *alloc, void *pointer);

void destroy_alloc(PoolAllocator *alloc);