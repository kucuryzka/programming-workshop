#include "pool_allocator.h"


typedef void (*Destructor)(void *data);
typedef void *(*Constructor)(void *value);
typedef struct gc_counter gc_counter;


struct gc_counter{
  size_t count;
  void *data;

  int is_marked;

  Destructor destructor;
  Constructor constructor;

  gc_counter **refs;
  int ref_size;

};


gc_counter *createObject(void *data, PoolAllocator *alloc, Constructor ctor,
                         Destructor dtor);
void addRef(gc_counter *obj);
void deleteRef(gc_counter *obj, PoolAllocator *alloc);
void mark(gc_counter *obj);
void sweep(PoolAllocator *alloc);