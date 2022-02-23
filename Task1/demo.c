#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "deque.h"

int *MAL;
#define mal(x) MAL = malloc(sizeof(int)); *MAL = x

int main()
{
	int *temp;
	Deque deq = Deque_init();

	assert((deq.front != NULL || deq.rear != NULL) == deq.size);

	mal(1);
	Deque_push_front(&deq, (void *) MAL);
	assert(deq.front == deq.rear);

	assert( *((int *) Deque_pop_front(&deq)) == 1);
	assert(Deque_size(&deq) == 0);
	assert(Deque_pop_front(&deq) == NULL);
	assert(Deque_size(&deq) == 0);

	Deque_push_front(&deq, (void *) MAL);
	assert(*((int *)Deque_pop_rear(&deq)) == 1);
	assert(Deque_size(&deq) == 0);
	assert(Deque_pop_rear(&deq) == NULL);
	assert(Deque_size(&deq) == 0);

	Deque_push_front(&deq, (void *) MAL);

	mal(2);
	Deque_push_front(&deq, (void *) MAL);
	assert(deq.front != deq.rear);
	assert(Deque_size(&deq) == 2);

	// printf("GET: %d\n", *((int *) Deque_get_front(&deq)));
	// printf("GET: %d\n", *((int *) Deque_get_rear(&deq)));

	assert( *((int *) Deque_pop_front(&deq)) == 2);
	Deque_push_front(&deq, (void *) MAL);
	assert( *((int *) Deque_get_rear(&deq)) == 1);

	mal(3);
	Deque_push_front(&deq, (void *)MAL);

	mal(4);
	Deque_push_front(&deq, (void *)MAL);
	assert(Deque_size(&deq) == 4);
	assert( *((int *) Deque_pop_front(&deq)) == 4);
	assert(Deque_size(&deq) == 3);
	Deque_push_front(&deq, (void *)MAL);
	assert(Deque_size(&deq) == 4);

	mal(5);
	Deque_push_front(&deq, (void *)MAL);
	assert(*((int *)Deque_get_front(&deq)) == 5);
	assert(*((int *)Deque_get_rear(&deq)) == 1);
	assert(Deque_size(&deq) == 5);

	mal(-1);
	Deque_push_rear(&deq, (void *)MAL);
	// printf("GET: %d\n", *((int *) Deque_get_rear(&deq)));
	assert(*((int *)Deque_get_rear(&deq)) == -1);
	assert(Deque_size(&deq) == 6);

	// Deque_print(&deq);

	mal(-2);
	Deque_push_rear(&deq, (void *)MAL);
	mal(-3);
	Deque_push_rear(&deq, (void *)MAL);
	mal(-4);
	Deque_push_rear(&deq, (void *)MAL);
	mal(-5);
	Deque_push_rear(&deq, (void *)MAL);
	// printf("GET: %d\n", *((int *) Deque_get_rear(&deq)));

	temp = ((int *)Deque_get_rear(&deq));
	assert(*temp == -5);
	assert(Deque_size(&deq) == 10);

	temp = ((int *)Deque_pop_rear(&deq));
	assert(*temp == -5);
	assert(Deque_size(&deq) == 9);
	free(temp);

	temp = ((int *)Deque_pop_front(&deq));
	assert(*temp == 5);
	assert(Deque_size(&deq) == 8);
	free(temp);
	
	Deque_destroy(&deq);
	assert(Deque_size(&deq) == 0);
	assert(deq.front == NULL);
	assert(deq.rear == NULL);

	// Deque_print(&deq);

	return 0;
}
