#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"  // IWYU pragma: keep
#include "object.h"  // IWYU pragma: keep

#define ALLOCATE(type, count) (type*)reallocate(NULL, 0, sizeof(type) * (count))

#define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define FREE_ARRAY(type, pointer, old_count) reallocate(pointer, sizeof(type) * (old_count), 0)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
  (type*)reallocate(pointer, sizeof(type) * (old_count), sizeof(type) * (new_count))

void* reallocate(void* pointer, size_t old_size, size_t new_size);
void markObject(Obj* object);
void markValue(Value value);
void collectGarbage();
void freeObjects();

#endif  // !clox_memory_h
