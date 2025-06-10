#include "garbage_collector.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

gc_counter *createObject(void *data, PoolAllocator *alloc, Constructor ctor,
                         Destructor dtor) {
  gc_counter *obj = allocate(alloc);
  if (!obj) {
    return NULL;
  }

  obj->count = 1;
  obj->is_marked = 0;
  obj->constructor = ctor;
  obj->destructor = dtor;
  obj->refs = NULL;
  obj->ref_size = 0;
  obj->data = data;

  if (ctor) {
    ctor(obj->data);
  }

  return obj;
}

void addRef(gc_counter *obj) {
  if (obj)
    obj->count++;
}

void deleteRef(gc_counter *obj, PoolAllocator *alloc) {
  if (!obj)
    return;

  obj->count--;
  if (obj->count == 0) {
    if (obj->destructor && obj->data) {
      obj->destructor(obj->data);
    }

    if (obj->refs) {
      free(obj->refs);
      obj->refs = NULL;
    }

    free_alloc(alloc, obj);
  }
}

void mark(gc_counter *obj) {
  if (!obj || obj->is_marked == 1) {
    return;
  }

  obj->is_marked = 1;
  for (int i = 0; i < obj->ref_size; i++) {
    mark(obj->refs[i]);
  }
}

void sweep(PoolAllocator *alloc) {
  char *current_block = alloc->memory;
  for (size_t i = 0; i < alloc->block_num; i++) {
    gc_counter *obj = (gc_counter *)(current_block + sizeof(MemoryBlock));

    if (!obj)
      continue;

    if (obj->is_marked == 0 && obj->count == 0) {
      if (obj->destructor) {
        obj->destructor(obj->data);
      }

      free_alloc(alloc, obj);
    } else {
      obj->is_marked = 0;
    }
    current_block += sizeof(MemoryBlock) + alloc->block_size;
  }
}
