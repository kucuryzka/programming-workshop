#include "pool_allocator.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void alloc_init(PoolAllocator *alloc, size_t block_num, size_t block_size) {
  alloc->block_size = block_size;
  alloc->block_num = block_num;
  alloc->free_block = NULL;

  alloc->memory =
      (char *)malloc((sizeof(MemoryBlock) + block_size) * block_num);

  if (!alloc->memory) {
    return;
  }

  char *current_block = alloc->memory;
  for (size_t i = 0; i < block_num; ++i) {
    MemoryBlock *block = (MemoryBlock *)current_block;

    block->next = alloc->free_block;
    alloc->free_block = block;
    current_block += sizeof(MemoryBlock) + block_size;
  }
}

void *allocate(PoolAllocator *alloc) {
  if (!alloc->free_block) {
    return NULL;
  }

  MemoryBlock *block = alloc->free_block;
  alloc->free_block = block->next;

  return (void *)(block + 1);
}

void free_alloc(PoolAllocator *alloc, void *pointer) {
  if (!pointer) {
    return;
  }

  MemoryBlock *block = ((MemoryBlock *)pointer) - 1;

  block->next = alloc->free_block;
  alloc->free_block = block;
}