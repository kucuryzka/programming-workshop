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

  int value = 42;
  assert(hash_table_insert(&table, "key1", &value, sizeof(int)) == 0);

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
  assert(hash_table_insert(&table, "key1", &value, sizeof(int)) == 0);

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
    assert(hash_table_insert(&table, key, &values[i], sizeof(int)) == 0);
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

void test_allocator_overflow() {
  PoolAllocator allocator;
  alloc_init(&allocator, 2, sizeof(hash_table_entry));

  hash_table table;
  hash_table_init(&table, 5, &allocator);

  int v1 = 1, v2 = 2, v3 = 3;
  assert(hash_table_insert(&table, "key1", &v1, sizeof(int)) == 0);
  assert(hash_table_insert(&table, "key2", &v2, sizeof(int)) == 0);
  assert(hash_table_insert(&table, "key3", &v3, sizeof(int)) == -1);

  assert(hash_table_get(&table, "key1") != NULL);
  assert(hash_table_get(&table, "key2") != NULL);
  assert(hash_table_get(&table, "key3") == NULL);

  hash_table_free(&table);
}

void test_large_volume() {
  const size_t LARGE_SIZE = 1000;
  PoolAllocator allocator;
  alloc_init(&allocator, LARGE_SIZE, sizeof(struct hash_table_entry));

  hash_table table;
  hash_table_init(&table, 128, &allocator);

  for (int i = 0; i < LARGE_SIZE; i++) {
    char key[20];
    sprintf(key, "key_%d", i);
    int value = i;
    assert(hash_table_insert(&table, key, &value, sizeof(int)) == 0);
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
    hash_table_delete(&table, key);
  }

  for (int i = 0; i < LARGE_SIZE; i++) {
    char key[20];
    sprintf(key, "key_%d", i);
    int *val = (int *)hash_table_get(&table, key);
    if (i % 2 == 0) {
      assert(val == NULL);
    } else {
      assert(val != NULL);
      assert(*val == i);
    }
  }

  hash_table_free(&table);
}

void test_string_values() {
  PoolAllocator allocator;
  alloc_init(&allocator, 10, sizeof(struct hash_table_entry));
  hash_table table;
  hash_table_init(&table, 5, &allocator);

  const char *value = "test string";
  assert(hash_table_insert(&table, "str_key", value, strlen(value) + 1) == 0);

  char *retrieved = (char *)hash_table_get(&table, "str_key");
  assert(retrieved != NULL);
  assert(strcmp(retrieved, "test string") == 0);

  hash_table_free(&table);
}

int main() {
  test_init_free();
  test_insert_get();
  test_delete();
  test_collisions();
  test_allocator_overflow();
  test_large_volume();
  test_string_values();

  printf("All tests passed successfully!\n");
  return 0;
}
