#include "object.h"

#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "table.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, object_type) (type*)allocateObject(sizeof(type), object_type)

static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
  object->is_marked = false;

  object->next = vm.objects;
  vm.objects = object;

#if DEBUG_LOG_GC
  printf("%p allocate %zu for %d\n", (void*)object, size, type);
#endif

  return object;
}

ObjArray* newArray() {
  ObjArray* array = ALLOCATE_OBJ(ObjArray, OBJ_ARRAY);
  initValueArray(&array->elements);
  return array;
}

ObjArray* newArrayWithCapacity(int capacity) {
  ObjArray* array = ALLOCATE_OBJ(ObjArray, OBJ_ARRAY);
  initValueArray(&array->elements);

  if (capacity > 0) {
    array->elements.capacity = capacity;
    array->elements.values = GROW_ARRAY(Value, NULL, 0, capacity);
  }

  return array;
}

ObjBoundMethod* newBoundMethod(Value receiver, ObjClosure* method) {
  ObjBoundMethod* bound = ALLOCATE_OBJ(ObjBoundMethod, OBJ_BOUND_METHOD);
  bound->receiver = receiver;
  bound->method = method;
  return bound;
}

ObjClass* newClass(ObjString* name) {
  ObjClass* klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
  klass->name = name;
  initTable(&klass->methods);
  return klass;
}

ObjClosure* newClosure(ObjFunction* function) {
  ObjUpvalue** upvalues = ALLOCATE(ObjUpvalue*, function->upvalue_count);
  for (int i = 0; i < function->upvalue_count; i++) {
    upvalues[i] = NULL;
  }

  ObjClosure* closure = ALLOCATE_OBJ(ObjClosure, OBJ_CLOSURE);
  closure->function = function;
  closure->upvalues = upvalues;
  closure->upvalue_count = function->upvalue_count;
  return closure;
}

ObjFunction* newFunction() {
  ObjFunction* function = ALLOCATE_OBJ(ObjFunction, OBJ_FUNCTION);
  function->arity = 0;
  function->upvalue_count = 0;
  function->name = NULL;
  initChunk(&function->chunk);
  return function;
}

ObjInstance* newInstance(ObjClass* klass) {
  ObjInstance* instance = ALLOCATE_OBJ(ObjInstance, OBJ_INSTANCE);
  instance->klass = klass;
  initTable(&instance->fields);
  return instance;
}

ObjNative* newNative(NativeFn function) {
  ObjNative* native = ALLOCATE_OBJ(ObjNative, OBJ_NATIVE);
  native->function = function;
  return native;
}

static ObjString* allocateString(char* chars, int length, uint32_t hash) {
  ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  string->hash = hash;

  push(OBJ_VAL(string));
  tableSet(&vm.strings, string, NIL_VAL);
  pop();

  return string;
}

// Scramble does bytes FNV-1a http://www.isthe.com/chongo/tech/comp/fnv/
static uint32_t hashString(const char* key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}

ObjString* takeString(char* chars, int length) {
  uint32_t hash = hashString(chars, length);
  ObjString* interned = tableFindString(&vm.strings, chars, length, hash);

  if (interned != NULL) {
    FREE_ARRAY(char, chars, length + 1);
    return interned;
  }

  return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length) {
  uint32_t hash = hashString(chars, length);

  ObjString* interned = tableFindString(&vm.strings, chars, length, hash);

  if (interned != NULL) return interned;

  char* heap_chars = ALLOCATE(char, length + 1);
  memcpy(heap_chars, chars, length);
  heap_chars[length] = '\0';
  return allocateString(heap_chars, length, hash);
}

ObjUpvalue* newUpvalue(Value* slot) {
  ObjUpvalue* upvalue = ALLOCATE_OBJ(ObjUpvalue, OBJ_UPVALUE);
  upvalue->location = slot;
  upvalue->closed = NIL_VAL;
  upvalue->next = NULL;
  return upvalue;
}

static void printFunction(ObjFunction* function) {
  if (function->name == NULL) {
    printf("<script>");
    return;
  }
  printf("<fn %s>", function->name->chars);
}

static void printArray(ObjArray* array) {
  printf("[");
  for (int i = 0; i < array->elements.count; i++) {
    printValue(array->elements.values[i]);
    if (i < array->elements.count - 1) printf(", ");
  }
  printf("]");
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_ARRAY: printArray(AS_ARRAY(value)); break;
    case OBJ_BOUND_METHOD: printFunction(AS_BOUND_METHOD(value)->method->function); break;
    case OBJ_CLASS: printf("%s", AS_CLASS(value)->name->chars); break;
    case OBJ_CLOSURE: printFunction(AS_CLOSURE(value)->function); break;
    case OBJ_FUNCTION: printFunction(AS_FUNCTION(value)); break;
    case OBJ_NATIVE: printf("<native fn>"); break;
    case OBJ_INSTANCE: printf("%s instance", AS_INSTANCE(value)->klass->name->chars); break;
    case OBJ_STRING: printf("%s", AS_CSTRING(value)); break;
    case OBJ_UPVALUE: printf("upvalue"); break;
  }
}
