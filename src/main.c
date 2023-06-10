
#include "../include/hash.h"
#include <stdio.h>

int main() {
  struct HashTable hashTable;

  initializeHashTable(&hashTable);

  char operation;
  int key;

  scanf("%c%d", &operation, &key);

  while (!feof(stdin)) {
    if (operation == 'i') {
      hashTableInsert(&hashTable, key);
    } else if (operation == 'r') {
      hashTableRemove(&hashTable, key);
    }

    scanf("%c%d", &operation, &key);
  }

  printHashTable(hashTable);

  return 0;
}
