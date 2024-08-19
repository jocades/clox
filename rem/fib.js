function fib(n) {
  if (n <= 1) return n
  return fib(n - 1) + fib(n - 2)
}

let N = 40

// let start = Date.now()
// let result = fib(N)
// let elapsed = Date.now() - start
//
// console.log(`fib(${N}) = ${result} (${elapsed}ms)`)
// console.log(`fib(${N}) = ${result} (${elapsed / 1000}s)`)

let MAX = 1_000_000

let start2 = Date.now()
for (let i = 0; i < MAX; i++) {}
let elapsed2 = Date.now() - start2
console.log(`for (let i = 0; i < ${MAX}; i++) {} (${elapsed2}ms)`)
console.log(`for (let i = 0; i < ${MAX}; i++) {} (${elapsed2 / 1000}s)`)

let arr = Array.from({ length: MAX })
let start3 = Date.now()
for (let i = 0; i < arr.length; i++) {}
let elapsed3 = Date.now() - start3
console.log(`for (let i = 0; i < arr.length; i++) {} (${elapsed3}ms)`)
console.log(`for (let i = 0; i < arr.length; i++) {} (${elapsed3 / 1000}s)`)

// for each
let start4 = Date.now()
arr.forEach(() => {})
let elapsed4 = Date.now() - start4
console.log(`arr.forEach(() => {}) (${elapsed4}ms)`)
console.log(`arr.forEach(() => {}) (${elapsed4 / 1000}s)`)
