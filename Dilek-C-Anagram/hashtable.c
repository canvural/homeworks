#include "hashtable.h"

HashTable *ht_create(size_t size)
{
  HashTable *ht = malloc(sizeof(*ht);
  ht->size = size;
  ht->buckets = malloc(sizeof(char*) * size);
  
  return ht;
}

int to_integer(char * key)
{
  if (ht == NULL || key == NULL)
    return -1;

  int hash = 0;
  int i;
  int len = strlen(key);
  
  for (i=0; i < len; i++)
    hash = 61 * hash + key[i];

  return hash;
}

int hash(char *key, HashTable * ht)
{
	
}
