#include <stdio.h>
#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES; // Shared variable

// Function to decrease available resources
int decrease_count(int count)
{
    if (available_resources < count)
    {
        return -1; // Not enough resources
    }
    else
    {
        available_resources -= count;
        return 0; // Successfully allocated resources
    }
}

// Function to increase available resources
void increase_count(int count)
{
    available_resources += count;
}

void *process(void *arg)
{
    int count = *(int *)arg;

    if (decrease_count(count) == 0)
    { // Try to allocate resources
        printf("Allocated %d resources, Remaining: %d\n", count, available_resources);

        // Simulating process execution time
        sleep(1);

        // Releasing the resources after use
        increase_count(count);
        printf("Released %d resources, Remaining: %d\n", count, available_resources);
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
