#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

void *decrease_count(void *arg)
{
    int count = *(int *)arg;

    if (available_resources >= count)
    {
        sleep(1); // Simulating delay
        available_resources -= count;
        printf("Resources Decreased: %d, Available: %d\n", count, available_resources);
    }
    else
    {
        printf("Insufficient resources for request: %d\n", count);
    }
    return NULL;
}

void *increase_count(void *arg)
{
    int count = *(int *)arg;
    sleep(1); // Simulating delay
    available_resources += count;
    printf("Resources Increased: %d, Available: %d\n", count, available_resources);
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;
    int req1 = 3, req2 = 2, req3 = 4;

    pthread_create(&t1, NULL, decrease_count, &req1);
    pthread_create(&t2, NULL, decrease_count, &req2);
    pthread_create(&t3, NULL, increase_count, &req3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Final Available Resources: %d\n", available_resources);
    return 0;
}
