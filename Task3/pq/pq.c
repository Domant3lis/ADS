#include <stdlib.h>
#include "pq.h"

PriorityQueue* pq_init()
{
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    if (!queue) {
        return NULL;
    }

    queue->head = NULL;
    return queue;
}

int pq_isEmpty(PriorityQueue* queue)
{
    return queue == NULL || queue->head == NULL;
}

void pq_insert(PriorityQueue* queue, void* data, size_t priority)
{
    if (!queue)
        return;

    Node* new = malloc(sizeof(Node));
    if (!new)
        return;

    new->data = data;
    new->priority = priority;

    // If head doesn't exist or is lower priority, set new node as head
    if (!queue->head || new->priority > queue->head->priority)
    {
        new->next = queue->head;
        queue->head = new;
        return;
    }

    // Search for location to insert node
    Node* iter = queue->head;
    while(iter->next != NULL && priority <= iter->next->priority)
        iter = iter->next;

    new->next = iter->next;
    iter->next = new;
}

// Remove element with highest priority
void* pq_remove(PriorityQueue* queue)
{
    if (!queue || queue->head == NULL)
        return NULL;

    void* data = queue->head->data;
    Node* old = queue->head;

    if (queue->head->next != NULL)
        queue->head = queue->head->next;
    else
        queue->head = NULL;

    free(old);
    return data;
}

void pq_join(PriorityQueue* a, PriorityQueue* b)
{
    if (!a || !b || !b->head)
        return;

    if (!a->head && b->head)
    {
        a->head = b->head;
    }
    else
    {
        // Change a->head to b->head if b->head has higher priority
        if (b->head->priority > a->head->priority)
        {
            Node* node = b->head;
            b->head = b->head->next;

            node->next = a->head;
            a->head = node;
        }

        for(Node *itA = a->head, *itB = b->head; itB != NULL; )
        {
            // Find where to insert itB
            while(itA->next != NULL && itA->next->priority >= itB->priority)
                itA = itA->next;

            // If itA ends, attach the rest of itB onto it
            if (itA->next == NULL)
            {
                itA->next = itB;
                break;
            }

            // Save current node and insert it
            Node* node = itB;
            itB = itB->next;

            node->next = itA->next;
            itA->next = node;
        }
    }

    b->head = NULL;
}

size_t pq_size(PriorityQueue* queue)
{
    if (!queue || !queue->head)
        return 0;

    size_t size = 0;
    for(Node* it = queue->head; it != NULL; it = it->next)
        ++size;

    return size;
}

void pq_free(PriorityQueue* queue, void (*dataCallback)(void*))
{
    if (!queue)
        return;

    pq_clear(queue, dataCallback);

    free(queue);
    return;
}

void pq_clear(PriorityQueue* queue, void (*dataCallback)(void*))
{
    if (!queue || !queue->head)
        return;

    for(Node* next = queue->head; next != NULL;)
    {
        if (dataCallback != NULL)
            dataCallback(next->data);

        Node* prev = next;
        next = next->next;
        free(prev);
    }

    queue->head = NULL;
}

void pq_destroy(PriorityQueue *queue)
{
    if (!queue || !queue->head)
        return;

    for (Node *next = queue->head; next != NULL;)
    {
        Node *prev = next;
        next = next->next;
        free(prev);
    }

    queue->head = NULL;
}

void* pq_retrieve(PriorityQueue* queue)
{
    if ((queue == NULL) || (queue->head == NULL))
        return NULL;

    return queue->head->data;
}
