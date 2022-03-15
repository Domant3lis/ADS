// Domantas Keturakis ~ PS1 ~ Task1
#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

// #pragma GCC poison printf
#pragma GCC poison puts

struct Node
{
	void *value;
	Node *next;
	Node *prev;
};

// Initializes a Node on the heap
Node *Node_init(void *val)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL)
		return NULL;

	node->value = val;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

// Initializes the Deque
Deque Deque_init()
{
	Deque ret = {
		.size = 0,
		.front = NULL,
		.rear = NULL,
	};

	return ret;
}

// Returns the number of elements in the Deque `deq`
size_t Deque_size(Deque *deq)
	{ return deq->size; }

// Shows if Deque is empty i.e. if it's size is 0
// false => not empty
// true => empty
bool Deque_empty(Deque *deq)
{
	if (deq->size == 0)
		return true;    
	else
		return false;
}

// Adds the value to the front of the Deque
// Important: It is assumed that `val` is alloc'ed on the heap
// And thus will be free()'d once Deque is destroyed
Node *Deque_push_front(Deque *deq, void *val)
{
	++(deq->size);
	Node *new = Node_init(val);
	if (new == NULL)
		return NULL;

	if (deq->size == 1)
		deq->front = deq->rear = new;
	else
	{
		deq->front->next = new;
		new->prev = deq->front;
		deq->front = new;
	}
	return new;
}

// Adds the value to the front of the Deque
// Important: It is assumed that `val` is alloc'ed on the heap
// And thus will be free()'d once Deque is destroyed
Node *Deque_push_rear(Deque *deq, void *val)
{
	++(deq->size);
	Node *new = Node_init(val);
	if (new == NULL)
		return NULL;

	if (deq->size == 1)
		deq->front = deq->rear = new;
	else
	{
		deq->rear->prev = new;
		new->next = deq->rear;
		deq->rear = new;
	}

	return new;
}

// Removes the first element from the Deque
// and returns it
// IMPORTANT: pop'ed elements must be free()'d
// by the called and will not be handled by Deque_destroy() 
void *Deque_pop_front(Deque *deq)
{
	if(deq->size == 0)
		return NULL;
	else if (deq->size == 1)
	{
		void *ret = deq->front->value;
		free(deq->front);
		deq->front = NULL;
		deq->rear = NULL;
		
		--(deq->size);
		return ret;
	}
	else
	{
		void *ret = deq->front->value;
		deq->front = deq->front->prev;
		free(deq->front->next);
		deq->front->next = NULL;

		--(deq->size);
		return ret;
	}
}

// Removes the last element from the Deque
// and returns it
// IMPORTANT: pop'ed elements must be free()'d
// by the called and will not be handled by Deque_destroy()
void *Deque_pop_rear(Deque *deq)
{
	if (deq->size == 0)
		return NULL;
	else if (deq->size == 1)
	{
		void *ret = deq->front->value;
		free(deq->front);
		deq->front = NULL;
		deq->rear = NULL;

		--(deq->size);
		return ret;
	}
	else
	{
		void *ret = deq->rear->value;
		deq->rear = deq->rear->next;
		free(deq->rear->prev);
		deq->rear->prev = NULL;

		--(deq->size);
		return ret;
	}
}

// Returns the first element from the Deque without removing it
void *Deque_get_front(Deque *deq)
	{ return deq->front->value; }

// Returns the last element from the Deque without removing it
void *Deque_get_rear(Deque *deq)
	{ return deq->rear->value; }

// Destroys the Deque `deq`
// and free()'s all elements held inside
void Deque_destroy(Deque *deq)
{
	Node *temp = deq->front;
	while(temp != NULL)
	{
		free(temp->value);

		Node *fre = temp;
		temp = temp->prev;
		free(fre);
	}

	deq->size = 0;
	deq->front = NULL;
	deq->rear = NULL;
}

// Checks if more memory can be allocated to
// store another element in the Deque
bool Deque_full(void)
{
	Node *new = Node_init(NULL);
	if (new == NULL)
	{
		return true;
	}
	else
	{
		free(new);
		return false;
	}
}

void Deque_print(Deque *deq)
{
	Node *node = deq->front;
	while (node != NULL)
	{
		printf("%d ", *((int *)node->value));

		node = node->prev;
	}

	printf("\n");
}
