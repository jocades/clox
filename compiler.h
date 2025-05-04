#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"  // IWYU pragma: keep

bool compile(const char* source, Chunk* chunk);

#endif  // !clox_compiler_h
