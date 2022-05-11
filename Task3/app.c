#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "pq/pq.h"

#define VIP_CLIENT 1
#define REGULAR_CLIENT 0

typedef struct {
    unsigned short priority;
    int time_to_fix; // time to fix a car in hours
} Client;

typedef struct
{
    unsigned int starting_jobs;
    unsigned int sim_hours;
    unsigned short prob_new_client;
    unsigned int no_new_client;
    unsigned int number_of_workers;
    unsigned short prob_vip;
    unsigned int A;
    unsigned int A1;
    // B := A - A1
    long long hourly_pay;
} State;

void State_print(State st)
    { printf("START_JOBS: %u  SIM_HOURS: %u  PROB OF NEW CLIENT: %u%%  NO. WORKERS: %u  PROB VIP: %u%%  A: %u  A1: %u\n", st.starting_jobs, st.sim_hours, st.prob_new_client, st.number_of_workers, st.prob_vip, st.A, st.A1); }

void Client_print(Client *client)
{
    Client cln = *client;
    printf("PRIORITY: %-8s  "
        "TIME: %d\n", cln.priority ? "VIP" : "REGULAR", cln.time_to_fix);
}

unsigned short rand_vip(short prob_vip)
{
    return (prob_vip > (rand() % 100)) ? 1 : 0;
}

short rand_to_fix(short num_of_workers)
{
    return 1 + (rand() % (5 * num_of_workers));
}

bool rand_new_client(short prob_new_client)
{
    return ((rand() % 100) < prob_new_client) ? true : false;
}

// Initializes the `Client` struct on the heap
Client *Client_init_heap(short vip_prob, short num_of_workers)
{
    Client *ret = malloc(sizeof(Client));

    ret->priority = rand_vip(vip_prob);
    ret->time_to_fix = rand_to_fix(num_of_workers);

    return ret;
}

void Client_free(void *client)
{
    free(client);
    client = NULL;
}

#define CURRENT(queue) ((Client *) pq_retrieve(queue))
#define REMOVE(queue) Client_free(pq_remove(queue))
// Returns the cost of operating
long long simulate(State state, bool logs)
{
    assert(state.A >= state.A1);

    long long expenses = 0;
    long long revenue = 0;

    PriorityQueue *work_queue = pq_init();

    // Initial jobs
    for (unsigned int ix = 0; ix < state.starting_jobs; ++ix)
    {
        Client *client = Client_init_heap(state.prob_vip, state.number_of_workers);
        pq_insert(work_queue, client, client->priority);
    }

    if (logs)
    {
        puts("INIT QUEUE:");
        pq_iter(work_queue, cln, {
            Client_print(cln);
        });
    }

    unsigned int ix = 0;
    unsigned int hour = 0;
    while (ix < state.sim_hours)
    {
        long long payrate = state.hourly_pay;

        if (logs)
        {
            puts("-- QUEUE --");
            pq_iter(work_queue, el, {
                Client_print(el);
            });
        }

        // Simulation of one hour
        if (CURRENT(work_queue) != NULL)
        {
            // Regular conditions
            if (hour <= 8)
            {
                for (unsigned int jx = 0; jx < state.number_of_workers; ++jx)
                {
                    if (CURRENT(work_queue)->time_to_fix > 0)
                        CURRENT(work_queue)->time_to_fix -= 1;
                    else
                    {
                        while (CURRENT(work_queue) != NULL && CURRENT(work_queue)->time_to_fix <= 0)
                            REMOVE(work_queue);
                        
                        if (CURRENT(work_queue) == NULL)
                        {
                            // Idle pay
                            expenses += (state.number_of_workers - jx) * payrate; 
                            break;
                        }
                        
                        CURRENT(work_queue)->time_to_fix -= 1;
                    }

                    assert(CURRENT(work_queue)->time_to_fix >= 0);
                    expenses += payrate;
                }
            }
            // Incase a VIP client appears
            // and workers need to work overtime
            else while ( CURRENT(work_queue) != NULL
                && CURRENT(work_queue)->priority == VIP_CLIENT
                && state.sim_hours > ix )
            {
                for (unsigned int jx = 0; jx < state.number_of_workers; ++jx)
                {
                    if (CURRENT(work_queue)->time_to_fix > 0)
                        CURRENT(work_queue)->time_to_fix -= 1;

                    // work on a car has finished
                    else
                    {
                        REMOVE(work_queue);
                        // No more cars in the queue
                        if (CURRENT(work_queue) == NULL)
                            break;
                        // No more VIP clients
                        if (CURRENT(work_queue)->priority != VIP_CLIENT)
                            break;

                        CURRENT(work_queue)->time_to_fix -= 1;
                        revenue += state.A1;
                    }

                    assert(CURRENT(work_queue)->time_to_fix >= 0);
                    expenses += payrate * 2;
                }

                ++ix;
            }
        }
        else // if (CURRENT(work_queue) == NULL)
        {
            // Idle pay
            expenses += payrate * state.number_of_workers;
        }

        // Generates new clients
        if (rand_new_client(state.prob_new_client))
        {
            Client *client = Client_init_heap(state.prob_vip, state.number_of_workers);
            pq_insert(work_queue, client, client->priority);
        }

        hour = (hour > 8) ? 0 : hour + 1;
        ++ix;
    }

    pq_free(work_queue, &Client_free);

    return revenue - expenses;
}

int main()
{
    const int TRIES = 5;

    srand(time(NULL));

    State s = {
        .starting_jobs = 3,
        .sim_hours = 100,
        .prob_new_client = 25,
        .number_of_workers = 2,
        .prob_vip = 0,
        .A = 100,
        .A1 = 20,
        .hourly_pay = 20,
        .no_new_client = 5,
    };
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
        printf("TOTAL: %lld\n", simulate(s, false));
    puts("------");

    s = (State){
        .starting_jobs = 5,
        .sim_hours = 100,
        .prob_new_client = 25,
        .number_of_workers = 2,
        .prob_vip = 25,
        .A = 100,
        .A1 = 20,
        .hourly_pay = 20,
        .no_new_client = 5,
    };
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
        printf("TOTAL: %lld\n", simulate(s, false));
    puts("------");

    s = (State){
        .starting_jobs = 5,
        .sim_hours = 100,
        .prob_new_client = 25,
        .number_of_workers = 2,
        .prob_vip = 50,
        .A = 100,
        .A1 = 20,
        .hourly_pay = 20,
        .no_new_client = 5,
    };

    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
        printf("TOTAL: %lld\n", simulate(s, false));
    puts("------");

    s = (State){
        .starting_jobs = 5,
        .sim_hours = 100,
        .prob_new_client = 25,
        .number_of_workers = 2,
        .prob_vip = 75,
        .A = 100,
        .A1 = 20,
        .hourly_pay = 20,
        .no_new_client = 5,
    };
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
        printf("TOTAL: %lld\n", simulate(s, false));
    puts("------");

    s = (State){
        .starting_jobs = 5,
        .sim_hours = 100,
        .prob_new_client = 25,
        .number_of_workers = 2,
        .prob_vip = 100,
        .A = 100,
        .A1 = 20,
        .hourly_pay = 20,
        .no_new_client = 5,
    };
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
        printf("TOTAL: %lld\n", simulate(s, false));
    puts("------");

    return 0;
}
