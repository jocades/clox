#include <stdio.h>
#include <time.h>

int fib(int n) {
  if (n <= 1) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

int main(int argc, const char *argv[]) {
  int N = 40;
  long start = clock();
  int result = fib(N);
  long elapsed = clock() - start;
  printf("fib(%d) = %d (%ldms)\n", N, result, elapsed);
  printf("fib(%d) = %d (%fs)\n", N, result, (double)elapsed / CLOCKS_PER_SEC);
  return 0;
}
