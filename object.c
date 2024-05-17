#include "object.h"

#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, object_type) \
  (type*)allocateObject(sizeof(type), object_type)

static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
  return object;
}

static ObjString* allocateString(char* chars, int length) {
  ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  return string;
}

ObjString* copyString(const char* chars, int length) {
  char* heap_chars = ALLOCATE(char, length + 1);
  memcpy(heap_chars, chars, length);
  heap_chars[length] = '\0';
  return allocateString(heap_chars, length);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING: printf("%s", AS_CSTRING(value)); break;
  }
}
