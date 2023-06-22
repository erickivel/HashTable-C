#ifndef HASH_H
#define HASH_H

#define TABLE_SIZE 11

struct Slot {
  int value;
  enum { EMPTY, VALID, EXCLUDED } status;
};

struct HashTable {
  struct Slot table1[TABLE_SIZE];
  struct Slot table2[TABLE_SIZE];
};

void initializeHashTable(struct HashTable *hashTable);

int hashTableSearch(struct HashTable hashTable, int key);

void hashTableInsert(struct HashTable *hashTable, int key);

void hashTableRemove(struct HashTable *hashTable, int key);

void printHashTable(struct HashTable hashTable);

#endif
