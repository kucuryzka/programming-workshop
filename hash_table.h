#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "pool_allocator.h"
#include <stddef.h>

typedef struct hash_table_entry {
  char *key;
  void *value;
  struct hash_table_entry *next;
} hash_table_entry;

typedef struct {
  hash_table_entry **buckets;
  size_t capacity;
  PoolAllocator *allocator;
} hash_table;

void hash_table_init(hash_table *table, size_t capacity,
                     PoolAllocator *allocator);
int hash_table_insert(hash_table *table, const char *key, void *value);
void *hash_table_get(hash_table *table, const char *key);
void hash_table_delete(hash_table *table, const char *key);
void hash_table_free(hash_table *table);

#endif
