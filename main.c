#include "linear_allocator.h"
#include <assert.h>
#include <stdio.h>

void test_alloc_init() {
  LinearAllocator alloc;
  AllocInit(&alloc, 128);

  assert(alloc.pointer != NULL);
}

void test_alloc_init_null() {
  LinearAllocator alloc;
  AllocInit(&alloc, (size_t)-1);

  assert(alloc.pointer == NULL);
}

void test_allocation() {
  LinearAllocator alloc;
  AllocInit(&alloc, 1024);

  int *num = (int *)Allocate(&alloc, sizeof(int));

  assert(num != NULL);
  assert(alloc.current == 4);
}

void test_aloccation_over_limit() {
  LinearAllocator alloc;
  AllocInit(&alloc, 2);

  int *num = (int *)Allocate(&alloc, sizeof(int));

  assert(num == NULL);
}

void test_alloc_free() {
  LinearAllocator alloc;
  AllocInit(&alloc, 16);

  assert(alloc.pointer != NULL);
  assert(alloc.total_size != 0);

  int *n = (int *)Allocate(&alloc, sizeof(int));

  Free(&alloc);
  assert(alloc.pointer == NULL);
  assert(alloc.current == 0);
  assert(alloc.total_size == 0);
}

int main(void) {
  test_alloc_init();

  test_alloc_init_null();

  test_allocation();

  test_aloccation_over_limit();

  test_alloc_free();
}
