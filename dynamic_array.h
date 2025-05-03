#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "linear_allocator.h"

typedef struct {
  void **data;
  size_t capacity;
  size_t size;
  LinearAllocator *allocator;
} ArrayList;

void arraylist_init(ArrayList *list, LinearAllocator *allocator,
                    size_t initial_capacity);
void arraylist_add(ArrayList *list, void *data, size_t index);
void *arraylist_get(ArrayList *list, size_t index);
void arraylist_del(ArrayList *list, size_t index);
void arraylist_free(ArrayList *list);

#endif