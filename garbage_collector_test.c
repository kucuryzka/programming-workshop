#include "garbage_collector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void test_alloc_init() {
    PoolAllocator alloc;
    alloc_init(&alloc, 4, 16);
  
    assert(alloc.block_num == 4);
    assert(alloc.block_size == 16);
    assert(alloc.memory != NULL);
    assert(alloc.free_block != NULL);
}


void test_create_object() {
  PoolAllocator alloc;
  alloc_init(&alloc, 10, sizeof(gc_counter));

  gc_counter *obj = createObject(NULL, &alloc, NULL, NULL);

  assert(obj != NULL);
  assert(obj->count == 1);
  assert(obj->is_marked == 0);

  deleteRef(obj, &alloc);

  assert(alloc.free_block != NULL);
}

void test_ref_count() {
  PoolAllocator alloc;
  alloc_init(&alloc, 1, sizeof(gc_counter));

  gc_counter *obj = createObject(NULL, &alloc, NULL, NULL);

  addRef(obj);
  assert(obj->count == 2);

  deleteRef(obj, &alloc);
  assert(obj->count == 1);

  deleteRef(obj, &alloc);
  assert(alloc.free_block != NULL);
}

void test_cycle() {
  PoolAllocator alloc;
  alloc_init(&alloc, 10, sizeof(gc_counter));

  gc_counter *A = createObject(NULL, &alloc, NULL, NULL);
  gc_counter *B = createObject(NULL, &alloc, NULL, NULL);
  assert(A != NULL);
  assert(B != NULL);

  A->refs = (gc_counter **)malloc(sizeof(gc_counter *));
  A->refs[0] = B;
  A->ref_size = 1;

  B->refs = (gc_counter **)malloc(sizeof(gc_counter *));
  B->refs[0] = A;
  B->ref_size = 1;

  A->count = 0;
  B->count = 0;


  mark(A);
  sweep(&alloc);


  assert(alloc.free_block != NULL);

  
}

int main() {
    test_alloc_init();
    test_create_object();
    test_ref_count();
    test_cycle();
}