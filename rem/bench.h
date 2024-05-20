#ifndef clox_bench_h
#define clox_bench_h

#include "time.h"

#define BENCH_START() clock_t start = clock()
#define BENCH_END() clock_t end = clock();
#define TO_MS(t) ((double)(t) / CLOCKS_PER_SEC * 1000)
#define TO_SEC(t) ((double)(t) / CLOCKS_PER_SEC)

#define BENCH_PRINT_MS() printf("Time: %fms\n", TO_MS(end - start))
#define BENCH_PRINT_SEC() printf("Time: %fs\n", TO_SEC(end - start))

typedef void (*bench_fn)(void);

typedef struct {
  const char* name;
  bench_fn fn;
} Benk;

void run_bench(const Benk* benches, size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("Running %s\n", benches[i].name);
    BENCH_START();
    benches[i].fn();
    BENCH_END();
    BENCH_PRINT_MS();
  }
}

// example
void bench_example() {
  for (int i = 0; i < 1000000; i++) {
    // do nothing
  }
}

#endif  // !clox_bench_h
