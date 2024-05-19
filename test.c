#include <stdio.h>
#include <string.h>

#include "object.h"
#include "table.h"

void printTable(Table* table) {
  printf("Table capacity: %d\n", table->capacity);
  printf("Table count: %d\n", table->count);
  for (int i = 0; i <= table->capacity; i++) {
    Entry* entry = &table->entries[i];
    if (entry->key != NULL) {
      printf(
          "%s: %d -- %p\n", entry->key->chars, entry->value.type,
          entry->value.as.obj
      );
    } else {
      printf("---\n");
    }
  }
}

int main() {
  Table table;
  initTable(&table);

  printTable(&table);

  char* string = "hello";
  int length = strlen(string);
  printf("string: %s\n", string);
  printf("length: %d\n", length);

  ObjString* stringObj = takeString(string, length);
  printf("stringObj: %s\n", stringObj->chars);
  printf("stringObj->length: %d\n", stringObj->length);
  printf("stringObj->hash: %d\n", stringObj->hash);

  Value value;
  value.type = VAL_OBJ;
  value.as.obj = (Obj*)stringObj;
  printf("value: %d -- %p\n", value.type, value.as.obj);

  tableSet(&table, stringObj, value);

  printTable(&table);

  tableGet(&table, stringObj, &value);
  printf("value: %d -- %p\n", value.type, value.as.obj);

  tableDelete(&table, stringObj);
  printTable(&table);

  freeTable(&table);

  return 0;
}
