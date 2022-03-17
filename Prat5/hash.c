#include "hash.h"
#include <stdlib.h>

#pragma GCC poison printf puts

// Initializes HashTable on the heap
// A pointer to the HashTable is returned
// if memory for it is successfully allocated
// otherwise NULL is returned 
HashTable *HT_create(size_t capacity)
{
    // Allocates space for all dynamic arrays
    HashTable *ht = malloc(sizeof(HashTable));
    ht->objects = calloc(capacity, sizeof(void *));
    ht->keys = calloc(capacity, sizeof(int));
    ht->state = calloc(capacity, sizeof(State));

    if (NULL == ht || NULL == ht->objects || NULL == ht->keys)
    {
        // clean-up in case some, but not all, allocations have failed
        free(ht->keys);
        free(ht->objects);
        free(ht->state);
        free(ht);

        return NULL;
    }

    ht->capacity = capacity;
    ht->size = 0;

    for (size_t i = 0; i < capacity; ++i)
    {
        ht->state[i] = FREE;
    }

    return ht;
}

// This function can be (and should be) any cryptographic hash function
size_t hash(int x, size_t size)
{
    return ( ((size_t) x) * 715827883) % size;
}

// returns 0 if it is not possible to put
// more objects in the HashTable
// returns 1 if it is
int HT_put(HashTable *ht, int key, void *obj)
{
    // Checks if there is enough capacity
    // for an additional object
    if ((ht->capacity - 1) != ht->size)
    {
        size_t hashedKey = hash(key, ht->capacity);

        // Searches for 
        while (ht->state[hashedKey] == OCCUPIED)
        {
            ++hashedKey;
            hashedKey %= ht->capacity;
        }

        ht->keys[hashedKey] = key;
        ht->objects[hashedKey] = obj;
        ht->state[hashedKey] = OCCUPIED;

        ++(ht->size);
        return 1;
    }
    else
        return 0;
}

// Gets an element with the provided key
// if none is found NULL is returned 
void *HT_get(HashTable *ht, int key)
{
    size_t hashedKey = hash(key, ht->capacity);

    while (ht->state[hashedKey] != FREE)
    {
        if (ht->keys[hashedKey] == key && ht->state[hashedKey] == OCCUPIED)
            return ht->objects[hashedKey];

        ++hashedKey;
        hashedKey %= ht->capacity;
    }

    return NULL;
}

// Removes an element with provided key
// if that element with provided key
// cannot be found NULL is returned
// 
// NOTE: a removed element must be freed
// later by the caller 
void *HT_remove(HashTable *ht, int key)
{
    size_t hashedKey = hash(key, ht->capacity);

    do
    {
        if (ht->keys[hashedKey] == key && ht->state[hashedKey] == OCCUPIED)
        {
            ht->state[hashedKey] = DELETED;
            return ht->objects[hashedKey];
        }
        
        ++hashedKey;
        hashedKey %= ht->capacity;
    }
    while (ht->state[hashedKey] != FREE);

    return NULL;
}

// Destroys HashTable `h`
// All objects stored in it are left unfreed
// to also free objects see HT_free_with_objects
void HT_free(HashTable **h)
{
    HashTable *ht = *h;

    free(ht->keys);
    free(ht->objects);
    free(ht->state);
    free(ht);

    *h = NULL; 
}

// Destroys HashTable `h` with all objects inside it
// 
// `destroy_fun` is a function which takes stored objects
// as an argument and assumedly properly destroys it
// if NULL is passed as destroy_fun then free() is called instead 
// 
// NOTE: all objects must be allocated on the heap
void HT_free_with_objects(HashTable **h, void destroy_fun(void *))
{
    HashTable *ht = *h;

    if (destroy_fun == NULL)
        destroy_fun = free;

    for (size_t i = 0; i < ht->capacity; ++i)
        if (ht->state[i] == OCCUPIED)
            destroy_fun(ht->objects[i]);

    HT_free(h);
}
