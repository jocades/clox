#ifndef clox_table_h
#define clox_table_h

#include "common.h"  // IWYU pragma: keep
#include "value.h"

typedef struct {
  ObjString* key;
  Value value;
} Entry;

// The ratio of count to capacity is exactly the load factor of the hash table.
typedef struct {
  int count;
  int capacity;
  Entry* entries;  // array of buckets
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableSet(Table* table, ObjString* key, Value value);
bool tableDelete(Table* table, ObjString* key);
void tableAddAll(Table* from, Table* to);
ObjString* tableFindString(Table* table, const char* chars, int length, uint32_t hash);
void tableRemoveWhite(Table* table);
void markTable(Table* table);

#endif  // !clox_table_h
