#include "dynamic_array.h"
#include <assert.h>

static void test_init() {
  LinearAllocator alloc;
  AllocInit(&alloc, 1024);

  ArrayList list;
  arraylist_init(&list, &alloc, 0, sizeof(int));

  assert(list.size == 0);
  assert(list.capacity > 0);
  assert(list.allocator == &alloc);
  assert(list.element_size == sizeof(int));

  Free(&alloc);
}

static void test_add_get() {
  LinearAllocator alloc;
  AllocInit(&alloc, 1024);

  ArrayList list;
  arraylist_init(&list, &alloc, 2, sizeof(int));

  int a = 10, b = 20, c = 30;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 2);

  assert(list.size == 3);
  assert(*(int *)arraylist_get(&list, 1) == 20);

  Free(&alloc);
}

static void test_delete() {
  LinearAllocator alloc;
  AllocInit(&alloc, 1024);

  ArrayList list;
  arraylist_init(&list, &alloc, 3, sizeof(int));

  int vals[] = {10, 20, 30};
  for (int i = 0; i < 3; i++)
    arraylist_add(&list, &vals[i], i);

  arraylist_del(&list, 1);

  assert(list.size == 2);
  assert(*(int *)arraylist_get(&list, 1) == 30);

  Free(&alloc);
}

static void test_edge_cases() {
  LinearAllocator alloc;
  AllocInit(&alloc, 128);

  ArrayList list;
  arraylist_init(&list, &alloc, 1, sizeof(int));

  assert(arraylist_get(&list, 0) == NULL);

  int x = 42;
  arraylist_add(&list, &x, 1);
  assert(list.size == 0);

  Free(&alloc);
}

int main() {
  test_init();
  test_add_get();
  test_delete();
  test_edge_cases();
  return 0;
}
