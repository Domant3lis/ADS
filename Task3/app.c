#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "pq/pq.h"
#include <assert.h>
#include <stdbool.h>

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
    unsigned int starting_jobs;
    unsigned int sim_hours;
    unsigned short prob_new_client;
    unsigned int number_of_workers;
    unsigned short prob_vip;
    unsigned int A;
    unsigned int A1;
    // B := A - A1
    _Decimal32 hourly_pay;
} State;

void State_print(State st)
    { printf("START_JOBS: %u  SIM_HOURS: %u  PROB OF NEW CLIENT: %u  NO. WORKERS: %u  PROB VIP: %u  A: %u  A1: %u\n", st.starting_jobs, st.sim_hours, st.prob_new_client, st.number_of_workers, st.prob_vip, st.A, st.A1); }

void Client_print(Client cln)
{
    printf("PRIORITY: %s  TIME: %u\n", cln.priority ? "VIP" : "REGULAR", cln.time_to_fix);
}

short rand_vip(short prob_vip)
{
    return (prob_vip > (rand() % 100)) ? 1 : 0;
}

short rand_to_fix(short num_of_workers)
{
    return 1 + (rand() % (5 * num_of_workers));
}

bool rand_new_client(short prob_new_client)
{
    return ((rand() % 100) > prob_new_client) ? true : false;
}

// Initializes the `Client` struct on the stack
Client Client_init_stack(short vip_prob, short num_of_workers)
{
    Client ret = {
        .priority = rand_vip(vip_prob),
        .time_to_fix = rand_to_fix(num_of_workers),
    };

    return ret;
}

Client *Client_init_heap(short vip_prob, short num_of_workers)
{
    Client *ret = malloc(sizeof(Client));

    ret->priority = rand_vip(vip_prob);
    ret->time_to_fix = rand_to_fix(num_of_workers);

    return ret;
}

void Client_free(Client *client)
{
    free(client);
    client = NULL;
}

// Returns the cost of operating
// @arg sim_hours - number of hours to simulate operation of business
_Decimal32 simulate(State state)
{
    assert(state.A >= state.A1);

    State_print(state);

    [[maybe_unused]] _Decimal32 expenses = 0;
    [[maybe_unused]] _Decimal32 revenue = 0;

    PriorityQueue *work_queue = pq_init();
    for (unsigned int ix = 0; ix < state.starting_jobs; ++ix)
    {
        Client client = Client_init_stack(state.prob_vip, state.number_of_workers);
        pq_insert(work_queue, &client, client.priority);
    }

    unsigned int ix = 0;
    unsigned int hour = 0;
    Client current = *((Client *) pq_remove(work_queue));
    while (ix < state.sim_hours)
    {
        unsigned int needed_workers = (current.time_to_fix >= state.number_of_workers) ? state.number_of_workers : current.time_to_fix;

        if (current.priority == VIP_CLIENT)
        {
            while(current.time_to_fix > 0)
            {
                current.time_to_fix -= needed_workers;

                if(hour > 8)
                {
                    expenses += state.hourly_pay * 2 * needed_workers;
                }
                else
                {
                    expenses += state.hourly_pay * needed_workers;
                }

                needed_workers = (current.time_to_fix >= state.number_of_workers) ? state.number_of_workers : current.time_to_fix;
                ++hour;
                ++ix;
            }

            revenue += state.A1;
        }
        else
        {
            current.time_to_fix -= needed_workers;

            expenses += state.hourly_pay * needed_workers;

            needed_workers = (current.time_to_fix >= state.number_of_workers) ? state.number_of_workers : current.time_to_fix;
        }

        if (rand_new_client(state.prob_new_client))
        {
            Client client = Client_init_stack(state.prob_vip, state.number_of_workers);
            pq_insert(work_queue, &client, client.priority);
        }

        hour = (hour >= 8) ? 0 : hour + 1;
        ++ix;
    }

    pq_destroy(work_queue);

    return revenue - expenses;
}

int main()
{
    srand(time(NULL));

    // unsigned int sim_hours;
    // unsigned short number_of_workers;
    // unsigned short prob_vip;
    // unsigned int A;
    // unsigned int A1;
    // // B := A - A1
    // _Decimal32 hourly_pay;
    printf("TOTAL: %lf", (double) simulate((State) { 1, 10, 25, 2, 25, 100, 20, 20 }));

    // Client a = Client_init_stack(50, 10);
    // Client_print(a);
    // Client *a = Client_init_heap(50, 5);
    // Client_print(*a);

    // PriorityQueue *pq = pq_init();

    // pq_insert(pq, a, 0);

    // pq_free(pq, &Client_free);

    return 0;
}
