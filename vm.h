#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "table.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;            // the chunk of code we are executing
  uint8_t* ip;             // instruction pointer (points to the instructionn to be exec)
  Value stack[STACK_MAX];  // array of values (just a pointer) with a fixed size
  Value* stack_top;        // pointer to the top of the array (stack)
  Table globals;
  Table strings;  // table of strings
  Obj* objects;   // linked list of objects for the garbage collector
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
