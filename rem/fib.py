from time import time


def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)


N = 40

start = time()
result = fib(N)
elapsed = time() - start

print(f"fib({N}) = {result} ({elapsed:.2f}s)")
