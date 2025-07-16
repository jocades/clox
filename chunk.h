#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"  // IWYU pragma: keep
#include "value.h"

// Each instruction has a one-byte operation code.
// This OpCode enum controls which kind of instruction we are dealing with.
typedef enum {
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_POP,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_GET_GLOBAL,
  OP_DEFINE_GLOBAL,
  OP_SET_GLOBAL,
  OP_GET_UPVALUE,
  OP_SET_UPVALUE,
  OP_GET_PROPERTY,
  OP_SET_PROPERTY,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_CLOSURE,
  OP_CLOSE_UPVALUE,
  OP_RETURN,
  OP_CLASS,
} OpCode;

// A sequence of bytecode instructions that the VM will execute.
typedef struct {
  int count;             // number of bytes in the code array
  int capacity;          // number of bytes that can fit in the code array
  uint8_t* code;         // array of bytes
  int* lines;            // array of lines (parallel to code array)
  ValueArray constants;  // array of constants
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

#endif  // !clox_chunk_h
