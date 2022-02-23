#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct Deque
{
    Node *front;
    Node *rear;
    size_t size;
} Deque;

Deque Deque_init();
bool Deque_empty();
size_t Deque_size(Deque *deq);
Node *Deque_push_front(Deque *deq, void *val);
Node *Deque_push_rear(Deque *deq, void *val);
void *Deque_pop_front(Deque *deq);
void *Deque_get_front(Deque *deq);
void *Deque_get_rear(Deque *deq);
void *Deque_pop_rear(Deque *deq);
void Deque_destroy(Deque *deq);
bool Deque_full(void);
