#ifndef clox_vm_h
#define clox_vm_h

#include "object.h"
#include "table.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
  ObjClosure* closure;
  uint8_t* ip;
  Value* slots;
} CallFrame;

typedef struct {
  CallFrame frames[FRAMES_MAX];
  int frame_count;
  Value stack[STACK_MAX];  // array of values with a fixed size
  Value* stack_top;        // pointer to the top of the array (stack)
  Table globals;           // table of global variables
  Table strings;           // table of unique strings
  ObjString* init_string;
  ObjUpvalue* open_upvalues;  // linked list of upvalues that have not yet been closed

  size_t bytes_allocated;
  size_t next_gc;
  Obj* objects;  // linked list of objects for the garbage collector
  int gray_count;
  int gray_capacity;
  Obj** gray_stack;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif  // !clox_vm_h
