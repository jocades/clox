function fib(n) {
  if (n <= 1) return n
  return fib(n - 1) + fib(n - 2)
}

let N = 40

let start = Date.now()
let result = fib(N)
let elapsed = Date.now() - start

console.log(`fib(${N}) = ${result} (${elapsed}ms)`)
console.log(`fib(${N}) = ${result} (${elapsed / 1000}s)`)
