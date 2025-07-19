#ifndef clox_common_h
#define clox_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NAN_BOXING 1
#define DEBUG_PRINT_CODE 0
#define DEBUG_TRACE_EXECUTION 0

#define DEBUG_STRESS_GC 0
#define DEBUG_LOG_GC 0

#define UINT8_COUNT (UINT8_MAX + 1)

#define UNREACHABLE()                                                                            \
  do {                                                                                           \
    fprintf(stderr, "[%s:%d] Reached unreachable code in %s()\n", __FILE__, __LINE__, __func__); \
    abort();                                                                                     \
  } while (0)

#endif  // !clox_common_h
