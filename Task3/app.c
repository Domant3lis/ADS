#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "pq/pq.h"

enum PRIORITIES
{
    REGULAR_CLIENT = 0,
    VIP_CLIENT = 100,
};

typedef struct {
    enum PRIORITIES priority;
    unsigned int time_to_fix;
    unsigned int time_left_to_fix; // time to fix a car in hours
} Client;

typedef struct 
{
    unsigned int sim_hours;
    unsigned int number_of_workers;
    unsigned int probability_of_vip_client;
    _Decimal32 hourly_pay;

} State;


// Returns the cost of operating
// @arg sim_hours - number of hours to simulate operation of business
_Decimal32 simulate(State state)
{
    unsigned int ix = 0;
    while (ix < state.sim_hours)
    {

        ++ix;
    }

    return 0;
}

// Initializes the `Client` struct on the stack
#define Client_init_stack(prio, to_fix, left) \
{ \
    .priority = prio, \
    .time_to_fix = to_fix, \
    .time_left_to_fix = left, \
}

Client Client_init_heap(enum PRIORITIES prio, unsigned int to_fix, unsigned int left)
{
    Client *ret = malloc(sizeof(Client));

    ret->priority = prio;
    ret->time_to_fix = to_fix;
    ret->time_left_to_fix = left;

    return *ret;
}

void Client_free(Client *client) { free(client); client = NULL; }

int main()
{
    Client a = Client_init_stack(0, 1, 1);
    // Client b = Client_init_heap(0, 1, 1);

    PriorityQueue *pq = pq_create();

    _Decimal64 num0 = 1;
    _Decimal64 num1 = 10;
    _Decimal64 num = num0 + num1;

    pq_insert(pq, &num0, REGULAR_CLIENT);
    // pq_insert(pq, "LOL", REGULAR_CLIENT);
    // pq_insert(pq, "LOL", REGULAR_CLIENT);
    // pq_insert(pq, "LOL", REGULAR_CLIENT);
    pq_insert(pq, &num1, VIP_CLIENT);
    pq_insert(pq, &num1, VIP_CLIENT);
    pq_insert(pq, &num, REGULAR_CLIENT);

    pq_destroy(pq);
    free(pq);

    puts("Hello, World!");
    return 0;
}