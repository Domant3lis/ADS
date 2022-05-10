#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "pq/pq.h"

enum PRIORITIES
{
    REGULAR_CLIENT = 0,
    VIP_CLIENT = 1,
};

typedef struct {
    enum PRIORITIES priority;
    unsigned int time_to_fix; // time to fix a car in hours
} Client;

typedef struct 
{
    unsigned int sim_hours;
    unsigned int number_of_workers;
    unsigned int probability_of_vip_client;
    _Decimal32 hourly_pay;
} State;

void Client_print(Client cln)
{
    printf("PRIORITY: %s  TIME: %u\n", cln.priority ? "VIP" : "REGULAR", cln.time_to_fix);
}

short rand_vip(short probability_of_vip_client)
{
    return (probability_of_vip_client > (rand() % 100)) ? 1 : 0;
}

short rand_to_fix(short num_of_workers)
{
    return 1 + (rand() % (5 * num_of_workers));
}

// Initializes the `Client` struct on the stack
#define Client_init_stack(vip_prob, num_of_workers) \
    {                                              \
        .priority = rand_vip(vip_prob),                   \
        .time_to_fix = rand_to_fix(num_of_workers),       \
    } \

Client Client_init_heap(short vip_prob, short num_of_workers)
{
    Client *ret = malloc(sizeof(Client));

    ret->priority = rand_vip(vip_prob);
    ret->time_to_fix = rand_to_fix(num_of_workers);

    return *ret;
}

void Client_free(Client *client) { free(client); client = NULL; }

// Returns the cost of operating
// @arg sim_hours - number of hours to simulate operation of business
_Decimal32 simulate(State state)
{
    unsigned int ix = 0;
    _Decimal32 expenses;
    _Decimal32 revenue;
    while (ix < state.sim_hours)
    {
        
        ++ix;
    }

    return 0;
}

int main()
{
    srand(time(NULL));
    Client a = Client_init_stack(50, 10);
    Client_print(a);
    a = Client_init_heap(50, 5);
    Client_print(a);


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