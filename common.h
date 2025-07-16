#ifndef clox_common_h
#define clox_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION

// #define DEBUG_STRESS_GC
// #define DEBUG_LOG_GC

#define UINT8_COUNT (UINT8_MAX + 1)

#define UNREACHABLE()                                                                            \
  do {                                                                                           \
    fprintf(stderr, "[%s:%d] Reached unreachable code in %s()\n", __FILE__, __LINE__, __func__); \
    abort();                                                                                     \
  } while (false)

#endif  // !clox_common_h
