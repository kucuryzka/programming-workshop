#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_init_free() {
  PoolAllocator allocator;
  alloc_init(&allocator, 10, sizeof(struct hash_table_entry));

  hash_table table;
  hash_table_init(&table, 5, &allocator);

  assert(table.capacity == 5);
  assert(table.allocator == &allocator);

  hash_table_free(&table);
}

void test_insert_get() {
  PoolAllocator allocator;
  alloc_init(&allocator, 10, sizeof(struct hash_table_entry));
  hash_table table;
  hash_table_init(&table, 5, &allocator);

  int value = 42;
  assert(hash_table_insert(&table, "key1", &value) == 0);

  int *retrieved = (int *)hash_table_get(&table, "key1");
  assert(retrieved != NULL);
  assert(*retrieved == 42);

  hash_table_free(&table);
}

void test_delete() {
  PoolAllocator allocator;
  alloc_init(&allocator, 10, sizeof(struct hash_table_entry));
  hash_table table;
  hash_table_init(&table, 5, &allocator);

  int value = 100;
  hash_table_insert(&table, "key1", &value);

  hash_table_delete(&table, "key1");
  assert(hash_table_get(&table, "key1") == NULL);

  hash_table_free(&table);
}

void test_collisions() {
  PoolAllocator allocator;
  alloc_init(&allocator, 20, sizeof(struct hash_table_entry));
  hash_table table;
  hash_table_init(&table, 1, &allocator);

  int values[5] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    char key[10];
    sprintf(key, "key%d", i);
    assert(hash_table_insert(&table, key, &values[i]) == 0);
  }

  for (int i = 0; i < 5; i++) {
    char key[10];
    sprintf(key, "key%d", i);
    int *val = (int *)hash_table_get(&table, key);
    assert(val != NULL);
    assert(*val == i + 1);
  }

  hash_table_free(&table);
}

int main() {
  test_init_free();
  test_insert_get();
  test_delete();
  test_collisions();

  printf("All tests passed successfully!\n");
  return 0;
}
