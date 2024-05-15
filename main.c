#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  int constant1 = addConstant(&chunk, 2.3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant1, 123);

  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "test chunk");

  interpret(&chunk);

  freeVM();
  freeChunk(&chunk);

  return 0;
}