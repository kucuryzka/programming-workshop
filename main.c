#include "pool_allocator.h"
#include <assert.h>
#include <stdio.h>

void test_alloc_init() {
  PoolAllocator alloc;
  alloc_init(&alloc, 4, 16);

  assert(alloc.block_num == 4);
  assert(alloc.block_size == 16);
  assert(alloc.memory != NULL);
  assert(alloc.free_block != NULL);
}

void test_alloc_init_null() {
  PoolAllocator alloc;
  alloc_init(&alloc, (size_t)- 1, (size_t)-1);

  assert(alloc.memory == NULL);
}

void test_allocation() {
  PoolAllocator alloc;
  alloc_init(&alloc, 1024, 64);
  assert(alloc.memory != NULL);
  assert(alloc.free_block != NULL);

  void* pointer = allocate(&alloc);
  
  assert(pointer != NULL);
}

void test_aloccation_over_limit() {
  PoolAllocator alloc;
  alloc_init(&alloc, 1, 4);

  void *pointer1 = allocate(&alloc);
  void *pointer2 = allocate(&alloc);

  assert(pointer1 != NULL);
  assert(pointer2 == NULL);
}

void test_alloc_free() {
  PoolAllocator alloc;
  alloc_init(&alloc, 1, 4);

  void *pointer1 = allocate(&alloc);
  void *pointer2 = allocate(&alloc);
  assert(pointer1 != NULL);
  assert(pointer2 == NULL);

  free_alloc(&alloc, pointer1);
  void *pointer3 = allocate(&alloc);
  assert(pointer3 != NULL);
}

int main(void) {
  test_alloc_init();

  test_alloc_init_null();

  test_allocation();

  test_aloccation_over_limit();

  test_alloc_free();
}