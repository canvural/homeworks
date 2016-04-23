#ifndef HASTABLE_H
#define HASHTABLE_H

typedef struct HashTable {
  size_t size;
  char ** buckets;
} HashTable;

HashTable *ht_create(size_t size);
int to_integer(char *key);
int hash(char *key, HashTable * ht);
int hash1(char *key, HashTable * ht);
int hash2(char *key, HashTable * ht);
char *ht_get(char *key, HashTable * ht);
unsigned int ht_add(char *key, char *val, HashTable *ht);
unsigned int ht_remove(char *key, HashTable *ht);

#endif
