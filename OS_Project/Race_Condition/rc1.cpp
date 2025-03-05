#include <stdio.h>
#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES; // Shared variable

void *process(void *arg)
{
    int count = *(int *)arg;

    if (available_resources >= count)
    {                                 // Checking if enough resources exist
        available_resources -= count; // Decreasing resources
        printf("Allocated %d resources, Remaining: %d\n", count, available_resources);
    }
    else
    {
        printf("Not enough resources available for request: %d\n", count);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int req1 = 3, req2 = 4;

    pthread_create(&t1, NULL, process, &req1);
    pthread_create(&t2, NULL, process, &req2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final available resources: %d\n", available_resources);
    return 0;
}
