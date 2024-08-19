#include <stdio.h>
#include <time.h>

int fib(int n) {
  if (n <= 1) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

int main(int argc, const char* argv[]) {
  // int N = 40;
  // long start = clock();
  // int result = fib(N);
  // long elapsed = clock() - start;
  // // print milliseconds
  // printf(
  //     "fib(%d) = %d (%fms)\n", N, result,
  //     (double)elapsed / CLOCKS_PER_SEC * 1000
  // );
  // printf("fib(%d) = %d (%fs)\n", N, result, (double)elapsed /
  // CLOCKS_PER_SEC);

  int MAX = 10000000;  // 10M
  long start2 = clock();
  for (int i = 0; i < MAX; i++) {}
  long elapsed2 = clock() - start2;
  printf(
      "for (int i = 0; i < %d; i++) {} (%fms)\n", MAX,
      (double)elapsed2 / CLOCKS_PER_SEC * 1000
  );
  printf(
      "for (int i = 0; i < %d; i++) {} (%fs)\n", MAX,
      (double)elapsed2 / CLOCKS_PER_SEC
  );

  return 0;
}
