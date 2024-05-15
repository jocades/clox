#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// Each instruction has a one-byte operation code.
// This OpCode enum controls which kind of instruction we are dealing with.
typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN
} OpCode;

// A sequence of bytecode instructions that the VM will execute.
typedef struct {
  int count;            // number of bytes in the code array
  int capacity;         // number of bytes that can fit in the code array
  uint8_t *code;        // array of bytes
  int *lines;           // array of lines (parallel to code array)
  ValueArray constants; // array of constants
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);

#endif // !clox_chunk_h
