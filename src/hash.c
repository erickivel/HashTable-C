#include "../include/hash.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11

void initializeHashTable(struct HashTable *hashTable) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hashTable->table1[i].isValid = 0;
    hashTable->table2[i].isValid = 0;
  }
}

int h1(int key) { return key % TABLE_SIZE; }

int h2(int key) { return floor(TABLE_SIZE * (key * 0.9 - floor(key * 0.9))); }

int search(struct HashTable hashTable, int key) {
  int index = h1(key);

  if (hashTable.table1[index].isValid && hashTable.table1[index].value == key) {
    return index;
  } else if (!hashTable.table1[index].isValid) {
    index = h2(key);
    if (hashTable.table2[index].isValid &&
        hashTable.table2[index].value == key) {
      return index;
    }
  }

  return -1;
}

void hashTableInsert(struct HashTable *hashTable, int newKey) {
  int newKeyIndex = h1(newKey);
  int oldKey = hashTable->table1[newKeyIndex].value;

  if (hashTable->table1[newKeyIndex].isValid) {
    int oldKeyIndex = h2(oldKey);
    hashTable->table2[oldKeyIndex].value = oldKey;
    hashTable->table2[oldKeyIndex].isValid = 1;
  }

  hashTable->table1[newKeyIndex].value = newKey;
  hashTable->table1[newKeyIndex].isValid = 1;
}

void hashTableRemove(struct HashTable *hashTable, int key) {
  int index = h2(key);

  if (hashTable->table2[index].isValid &&
      hashTable->table2[index].value == key) {
    hashTable->table2[index].isValid = 0;
  } else {
    index = h1(key);
    if (hashTable->table1[index].isValid &&
        hashTable->table1[index].value == key) {
      hashTable->table1[index].isValid = 0;
    }
  }
}

int compareInt(const void *a, const void *b) { return *(int *)a - *(int *)b; }

void printHashTable(struct HashTable hashTable) {
  int orderedTable1[TABLE_SIZE];
  int orderedTable2[TABLE_SIZE];
  int count1 = 0;
  int count2 = 0;

  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hashTable.table1[i].isValid) {
      orderedTable1[count1] = hashTable.table1[i].value;
      count1++;
    }

    if (hashTable.table2[i].isValid) {
      orderedTable2[count2] = hashTable.table2[i].value;
      count2++;
    }
  }

  qsort(orderedTable1, count1, sizeof(int), compareInt);
  qsort(orderedTable2, count2, sizeof(int), compareInt);

  int max1 = count1;
  int max2 = count2;

  while (count1 > 0 || count2 > 0) {
    if (count1 <= 0) {
      printf("%d,T2,%d\n", orderedTable2[max2 - count2],
             h2(orderedTable2[max2 - count2]));
      count2--;

      continue;
    }

    if (count2 <= 0) {
      printf("%d,T1,%d\n", orderedTable1[max1 - count1],
             h1(orderedTable1[max1 - count1]));
      count1--;

      continue;
    }

    if (orderedTable1[max1 - count1] <= orderedTable2[max2 - count2]) {
      printf("%d,T1,%d\n", orderedTable1[max1 - count1],
             h1(orderedTable1[max1 - count1]));
      count1--;
    } else {
      printf("%d,T2,%d\n", orderedTable2[max2 - count2],
             h2(orderedTable2[max2 - count2]));
      count2--;
    }
  }
}
