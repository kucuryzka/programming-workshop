#include "dynamic_array.h"
#include <string.h>

#define DEFAULT_CAPACITY 16
#define GROWTH_FACTOR 2

void arraylist_init(ArrayList *list, LinearAllocator *allocator,
                    size_t initial_capacity) {
  size_t capacity = initial_capacity > 0 ? initial_capacity : DEFAULT_CAPACITY;
  list->data = Allocate(allocator, capacity * sizeof(void *));
  list->capacity = capacity;
  list->size = 0;
  list->allocator = allocator;
}

void arraylist_add(ArrayList *list, void *data, size_t index) {
  if (index > list->size)
    return;

  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * GROWTH_FACTOR;
    void **new_data = Allocate(list->allocator, new_capacity * sizeof(void *));
    memcpy(new_data, list->data, list->size * sizeof(void *));
    list->data = new_data;
    list->capacity = new_capacity;
  }

  if (index < list->size) {
    memmove(&list->data[index + 1], &list->data[index],
            (list->size - index) * sizeof(void *));
  }

  list->data[index] = data;
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (index >= list->size)
    return NULL;
  return list->data[index];
}

void arraylist_del(ArrayList *list, size_t index) {
  if (index >= list->size)
    return;

  if (index < list->size - 1) {
    memmove(&list->data[index], &list->data[index + 1],
            (list->size - index - 1) * sizeof(void *));
  }

  list->size--;
}

void arraylist_free(ArrayList *list) {
  list->data = NULL;
  list->capacity = 0;
  list->size = 0;
  list->allocator = NULL;
}