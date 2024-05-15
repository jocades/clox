// reminding myself about pointer arithmetic
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  int a = 10;
  int *p = &a;
  printf("a: %d\n", a);
  printf("p: %p\n", p);
  printf("*p: %d\n", *p);
  printf("p + 1: %p\n", p + 1);

  // accessing the next memory location which is not allocated to us
  // so it will print some garbage value or crash
  printf("*(p + 1): %d\n", *(p + 1));

  // arrays
  // an array is really just a pointer to the first element
  int arr[5] = {1, 2, 3, 4, 5};

  // acessing it will increase the pointer by the size of the type of the array
  // so for int it will increase by 4 bytes
  printf("arr: %p\n", arr);
  printf("arr + 1: %p\n", arr + 1);

  int first = *arr;
  int second = arr[1];
  // or
  int second2 = *(arr + 1);
  printf("first: %d\n", first);
  printf("second: %d\n", second);
  printf("second2: %d\n", second2);

  // strings
  // strings are just arrays of characters
  // and the last character is always '\0' so we need to allocate one more byte
  // than the length of the string
  // 'char' occupies 1 byte of memory

  char str[] = "hello";
  // same as
  char str2[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
  printf("str: %s\n", str);
  printf("str2: %s\n", str2);

  // we can access the characters in the string using the same pointer
  // arithmetic
  printf("str: %p\n", str);
  printf("str + 1: %p\n", str + 1);
  printf("*str: %c\n", *str);

  // allocating memory and freeing it
  // malloc() allocates memory on the heap and returns a pointer to it
  // free() deallocates the memory
  // we need to include stdlib.h for malloc() and free()
  // to create a struct we need to use malloc() to allocate memory for it
  struct Point {
    int x;
    int y;
  };

  struct Point *point = malloc(sizeof(struct Point));
  (*point).x = 5;
  point->x = 10;

  printf("point->x: %d\n", point->x);
  printf("point->y: %d\n", point->y);

  free(point);
  // we can still access the memory but it will contain garbage
  printf("point->x: %d\n", point->x);
  printf("point->y: %d\n", point->y);

  // when should we use malloc()?
  // when we need to allocate memory on the heap
  // when should we use free()?
  // when we are done with the memory and we want to deallocate it
  // we can use that memory for something else
  // what happens if we don't use free()?
  // the memory will be leaked and we will run out of memory
  // if we keep allocating memory and not freeing it
  // we can use valgrind to check for memory leaks
  // valgrind --leak-check=full ./a.out

  // casting
  // we can cast a pointer to a different type
  // but why and when should we do that?
  // when we need to access the memory as a different type
  // for example, we have a pointer to an integer but we need to access it as a
  // character we can cast the pointer to a character pointer
  int b = 65;
  int *pb = &b;
  char *pc = (char *)pb;
  printf("b: %d\n", b);
  printf("*pb: %d\n", *pb);
  printf("*pc: %c\n", *pc);

  // we can also cast a pointer to void pointer
  // void pointer is a generic pointer that can point to any type
  // but we can't dereference it directly
  // we need to cast it to the correct type before dereferencing it
  void *pv = pb;
  printf("*pv: %d\n", *(int *)pv);

  return 0;
}
