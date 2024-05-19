#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define BENCH_START() clock_t start = clock()
#define BENCH_END() clock_t end = clock();
#define TO_MS(t) ((double)(t) / CLOCKS_PER_SEC * 1000)
#define TO_SEC(t) ((double)(t) / CLOCKS_PER_SEC)

#define BENCH_PRINT_MS() printf("Time: %fms\n", TO_MS(end - start))
#define BENCH_PRINT_SEC() printf("Time: %fs\n", TO_SEC(end - start))

typedef void (*BenchFn)();
// a struct which will contain all the functions to run with their names
typedef struct {
  char* name;
  BenchFn fn;
} Bench;

void runBench(const char* name, Bench* benches, int count) {
  printf("== %s ==\n", name);
  for (int i = 0; i < count; i++) {
    printf("-- %s --\n", benches[i].name);
    BENCH_START();
    benches[i].fn();
    BENCH_END();
    BENCH_PRINT_MS();
    printf("\n");
  }
}

void benchStr() {
  char* str = "Hello, World!";
  printf("str: %p\n", str);
  printf("str + 1: %p\n", str + 1);
  printf("*str: %c\n", *str);
}

void benchMalloc() {
  struct Point {
    int x;
    int y;
  };

  struct Point* point = malloc(sizeof(struct Point));
  (*point).x = 5;
  point->x = 10;

  printf("point->x: %d\n", point->x);
  printf("point->y: %d\n", point->y);

  free(point);
  printf("point->x: %d\n", point->x);
  printf("point->y: %d\n", point->y);

  int b = 65;
  int* pb = &b;
  char* pc = (char*)pb;
  printf("b: %d\n", b);
  printf("*pb: %d\n", *pb);
  printf("*pc: %c\n", *pc);

  void* pv = pb;
  printf("*pv: %d\n", *(int*)pv);
}

int main() {
  Bench benches[] = {
      {"string", benchStr},
      {"malloc", benchMalloc},
  };

  runBench("test", benches, sizeof(benches) / sizeof(benches[0]));

  return 0;
}
