#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
  char* name;
  int age;
} User;

User* hash_table[TABLE_SIZE];

// unsigned int = 4 bytes = 32 bits = 2^32 = 4,294,967,296
unsigned int hash(char* name) {
  int length = strlen(name);
  unsigned int hash = 0;
  for (int i = 0; i < length; i++) {
    // printf("name[%d]: %c -> %d\n", i, name[i], name[i]);
    hash += name[i];
    hash *= name[i];
    hash %= TABLE_SIZE;
  }

  return hash;
}

void initHashTable() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

void printTable() {
  printf("Start\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == NULL) {
      printf("%i\t---\t%p\n", i, hash_table[i]);
    } else {
      printf(
          "%i\t%s\t%d\t%p\n", i, hash_table[i]->name, hash_table[i]->age,
          hash_table[i]
      );
    }
  }
  printf("End\n");
}

bool insert(char* key, User* value) {
  if (value == NULL) {
    return false;
  }

  int index = hash(key);
  printf("Key: %s\t Hash: %d\n", key, index);
  if (hash_table[index] != NULL) {
    return false;
  }

  hash_table[index] = value;
  return true;
}

User* get(char* key) {
  int index = hash(key);
  User* user = hash_table[index];

  if (user == NULL) {
    printf("Key %s not found. Index: %d, Pointer: %p\n", key, index, user);
  } else {
    printf("Key %s found. Index: %d, Pointer: %p\n", key, index, user);
  }

  if (user == NULL) {
    return NULL;
  }

  return user;
}

int main() {
  initHashTable();
  printTable();

  User john = {.name = "John", .age = 23};
  User jane = {.name = "Jane", .age = 25};
  User sara = {.name = "Sara", .age = 29};

  insert("john", &john);
  insert("jane", &jane);
  insert("sara", &sara);

  printTable();

  User* a = get("john");
  if (a == NULL) {
    printf("Not found!\n");
  } else {
    printf("Found %s\n", a->name);
  }

  User* b = get("jane");
  if (b == NULL) {
    printf("Not found!\n");
  } else {
    printf("Found %s\n", b->name);
  }

  /* char* names[12] = {"John", "Jane",  "Sara",  "Tom", "Lucy", "Mike",
                     "Mary", "Peter", "Alice", "Bob", "Eve",  "Jack"};

  for (int i = 0; i < 12; i++) {
    printf("%s -> %u\n", names[i], hash(names[i]));
  }
*/
  return 0;
}
