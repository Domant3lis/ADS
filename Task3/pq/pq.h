// Author: Domas Kalinauskas
#pragma once

#include <stddef.h>

typedef struct Node
{
    void* data;
    size_t priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue
{
    Node* head;
} PriorityQueue;

// Allocate queue
PriorityQueue* pq_init();

// Return true if queue is empty
int pq_isEmpty(PriorityQueue* queue);

// Insert data with priority
void pq_insert(PriorityQueue* queue, void* data, size_t priority);

// Removes highest priority node and returns data
void* pq_remove(PriorityQueue* queue);

// Merges priority queue b onto priority queue a
void pq_join(PriorityQueue* a, PriorityQueue* b);

// Return number of nodes in queue
size_t pq_size(PriorityQueue* queue);

// Free queue and nodes, and execute callback for each node if not NULL
void pq_free(PriorityQueue* queue, void (*dataCallback)(void*));

// Like pq_free, but doesn't free queue itself
void pq_clear(PriorityQueue* queue, void (*dataCallback)(void*));

// Like pq_free, but doesn't free the elements themselves
void pq_destroy(PriorityQueue *queue);

// Get data at front of queue without removing
void* pq_retrieve(PriorityQueue* queue);

// Iterate over priority queue's data held within each node
// queue - a pointer to the priority queue
// el_name - the name of each element used in fun
// fun - a block of code executed for each node
#define pq_iter_with_nodes(queue, node_name, fun) \
{                                                 \
    Node *(node_name) = (queue)->head;            \
    while ((node_name) != NULL)                   \
    {                                             \
        fun                                       \
        (node_name) = (node_name)->next;          \
    }                                             \
}

// Iterate over each priority queue node
// queue - a pointer to the priority queue
// el_name - the name of each element used in fun
// fun - a block of code executed for each node
#define pq_iter(queue, el_name, fun)                \
    pq_iter_with_nodes((queue), PQ_RESERVED_NAME, { \
        void *(el_name) = PQ_RESERVED_NAME->data;   \
        fun                                         \
    })
