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
    unsigned int B;
    // A1 := A - B
    long long hourly_pay;
    long long hourly_pay_overtime;
} State;

void State_print(State st)
    { printf("START_JOBS: %u  SIM_HOURS: %u  PROB OF NEW CLIENT: %u%%  NO. WORKERS: %u  PROB VIP: %u%%  A: %u  B: %u\n", st.starting_jobs, st.sim_hours, st.prob_new_client, st.number_of_workers, st.prob_vip, st.A, st.B); }

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
    assert(state.A >= state.B);

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
        if (logs)
        {
            puts("-- QUEUE --");
            pq_iter(work_queue, el, { Client_print(el); });
        }

        // Simulation of one hour
        if (CURRENT(work_queue) != NULL)
        {
            // Regular conditions
            if (hour <= 8)
            {
                // Each employee
                for (unsigned int jx = 0; jx < state.number_of_workers; ++jx)
                {
                    // Working on a car
                    if (CURRENT(work_queue)->time_to_fix > 0)
                        CURRENT(work_queue)->time_to_fix -= 1;
                    // A car was fixed
                    else
                    {
                        while (CURRENT(work_queue) != NULL && CURRENT(work_queue)->time_to_fix <= 0)
                        {
                            revenue += state.A;
                            REMOVE(work_queue);
                        }
                        
                        if (CURRENT(work_queue) == NULL)
                        {
                            // Idle pay
                            expenses += state.hourly_pay; 
                            break;
                        }
                        
                        CURRENT(work_queue)->time_to_fix -= 1;
                    }

                    assert(CURRENT(work_queue)->time_to_fix >= 0);
                    expenses += state.hourly_pay_overtime;
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

                        // else work for a VIP client continues
                        CURRENT(work_queue)->time_to_fix -= 1;
                        revenue += state.A;
                    }

                    assert(CURRENT(work_queue)->time_to_fix >= 0);
                    expenses += state.hourly_pay_overtime;
                }

                ++hour;
                ++ix;
            }
        }
        else // if (CURRENT(work_queue) == NULL)
        {
            // Idle pay
            expenses += state.hourly_pay * state.number_of_workers;
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
    long long sum = 0;

    srand(time(NULL));

    State s = {
        .starting_jobs = 3,
        .sim_hours = 100,
        .prob_new_client = 25,
        .number_of_workers = 2,
        .prob_vip = 0,
        .A = 100,
        .B = 80,
        .hourly_pay = 20,
        .no_new_client = 5,
    };
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
    {
        long long temp = simulate(s, false);
        sum += temp;
        printf("TOTAL: %lld\n", temp);
    }
    printf("AVERAGE: %lld\n", sum / TRIES);
    puts("------");

    sum = 0;
    s.prob_vip = 25;
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
    {
        long long temp = simulate(s, false);
        sum += temp;
        printf("TOTAL: %lld\n", temp);
    }
    printf("AVERAGE: %lld\n", sum / TRIES);
    puts("------");

    sum = 0;
    s.prob_vip = 50;
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
    {
        long long temp = simulate(s, false);
        sum += temp;
        printf("TOTAL: %lld\n", temp);
    }
    printf("AVERAGE: %lld\n", sum / TRIES);
    puts("------");

    sum = 0;
    s.prob_vip = 75;
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
    {
        long long temp = simulate(s, false);
        sum += temp;
        printf("TOTAL: %lld\n", temp);
    }
    printf("AVERAGE: %lld\n", sum / TRIES);
    puts("------");

    sum = 0;
    s.prob_vip = 100;
    State_print(s);
    for (int ix = 0; ix < TRIES; ++ix)
    {
        long long temp = simulate(s, false);
        sum += temp;
        printf("TOTAL: %lld\n", temp);
    }
    printf("AVERAGE: %lld\n", sum / TRIES);

    return 0;
}
