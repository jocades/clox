#include <stdio.h>
#include <stdlib.h>
// refreshing my mind about memory management in C
int main() {
  // malloc
  //
  // allocate 4 bytes of memory
  int* p = (int*)malloc(sizeof(int));
  // assign a value to the memory
  *p = 10;

  // realloc
  // it will change the size of the memory block pointed to by p to 8 bytes
  // and copy the existing data to the new memory block
  // if the new size is larger than the old size, the new memory will be
  // uninitialized if the new size is smaller than the old size, the data will
  // be truncated
  // if the new size is 0, it acts like free and returns NULL
  // if the old size is 0, it acts like malloc
  // if the old pointer is NULL, it acts like malloc
  // if the new size is the same as the old size, it does nothing

  p = (int*)realloc(p, sizeof(int) * 2);
  // assign a value to the new memory
  *(p + 1) = 20;

  printf("%d %d\n", *p, *(p + 1));

  // access memory outside the allocated memory
  int a = *(p + 2);
  printf("%d\n", a);

  return 0;
}
