#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

  int *value = malloc(sizeof(int));
  *value = 42;
  assert(hash_table_insert(&table, "key1", value) == 0);

  int *retrieved = (int *)hash_table_get(&table, "key1");
  assert(retrieved != NULL);
  assert(*retrieved == 42);

  free(retrieved); 
  hash_table_free(&table);
}

void test_delete() {
  PoolAllocator allocator;
  alloc_init(&allocator, 10, sizeof(struct hash_table_entry));
  hash_table table;
  hash_table_init(&table, 5, &allocator);

  int *value = malloc(sizeof(int));
  *value = 100;
  hash_table_insert(&table, "key1", value);

  hash_table_delete(&table, "key1");
  assert(hash_table_get(&table, "key1") == NULL);

  hash_table_free(&table);
}

void test_collisions() {
  PoolAllocator allocator;
  alloc_init(&allocator, 20, sizeof(struct hash_table_entry));
  hash_table table;
  hash_table_init(&table, 1, &allocator);

  int *values[5];
  for (int i = 0; i < 5; i++) {
    char key[10];
    sprintf(key, "key%d", i);
    values[i] = malloc(sizeof(int));
    *values[i] = i + 1;
    assert(hash_table_insert(&table, key, values[i]) == 0);
  }

  for (int i = 0; i < 5; i++) {
    char key[10];
    sprintf(key, "key%d", i);
    int *val = (int *)hash_table_get(&table, key);
    assert(val != NULL);
    assert(*val == i + 1);
  }

  for (int i = 0; i < 5; i++) {
    free(values[i]);
  }
  hash_table_free(&table);
}

void test_allocator_overflow() {
  PoolAllocator allocator;
  alloc_init(&allocator, 2, sizeof(hash_table_entry));

  hash_table table;
  hash_table_init(&table, 5, &allocator);

  int *v1 = malloc(sizeof(int));
  int *v2 = malloc(sizeof(int));
  int *v3 = malloc(sizeof(int));
  *v1 = 1; *v2 = 2; *v3 = 3;
  
  hash_table_insert(&table, "key1", v1);
  hash_table_insert(&table, "key2", v2);
  hash_table_insert(&table, "key3", v3);

  assert(hash_table_get(&table, "key3") == NULL);

  free(v1);
  free(v2);
  free(v3);
  hash_table_free(&table);
}

void test_large_volume() {
  const size_t LARGE_SIZE = 1000;
  PoolAllocator allocator;
  alloc_init(&allocator, LARGE_SIZE, sizeof(struct hash_table_entry));

  hash_table table;
  hash_table_init(&table, 128, &allocator);

  int *values[LARGE_SIZE];

  for (int i = 0; i < LARGE_SIZE; i++) {
    char key[20];
    sprintf(key, "key_%d", i);
    values[i] = malloc(sizeof(int));
    assert(values[i] != NULL);
    *values[i] = i;
    assert(hash_table_insert(&table, key, values[i]) == 0);
  }

  for (int i = 0; i < LARGE_SIZE; i++) {
    char key[20];
    sprintf(key, "key_%d", i);
    int *val = (int *)hash_table_get(&table, key);
    assert(val != NULL);
    assert(*val == i);
  }

  for (int i = 0; i < LARGE_SIZE; i += 2) {
    char key[20];
    sprintf(key, "key_%d", i);
    int *val = (int *)hash_table_get(&table, key);
    free(val); 
    hash_table_delete(&table, key);
  }

  for (int i = 1; i < LARGE_SIZE; i += 2) {
    char key[20];
    sprintf(key, "key_%d", i);
    assert(hash_table_get(&table, key) != NULL);
  }

  for (int i = 1; i < LARGE_SIZE; i += 2) {
    free(values[i]);
  }

  hash_table_free(&table);
}

int main() {
  test_init_free();
  test_insert_get();
  test_delete();
  test_collisions();
  test_allocator_overflow();
  test_large_volume();

  printf("All tests passed successfully!\n");
  return 0;
}
