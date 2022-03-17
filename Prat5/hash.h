#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    OCCUPIED = 0,
    DELETED = 1,
    FREE = 2,
} State;

typedef struct 
{
    State *state;
    int *keys;
    void **objects;

    size_t capacity;
    size_t size;
} HashTable;

HashTable *HT_create(size_t capacity);
int HT_put(HashTable *h, int key, void *obj);
void *HT_get(HashTable *ht, int key);
void *HT_remove(HashTable *ht, int key);
void HT_free(HashTable **h);
void HT_free_with_objects(HashTable **h, void destroy_fun(void *));
