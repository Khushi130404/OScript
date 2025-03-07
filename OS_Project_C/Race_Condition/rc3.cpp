#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex; // Mutex for atomic access
sem_t resource_sem;    // Semaphore for available resources

// Function to decrease resource count
void *decrease_count(void *arg)
{
    int count = *(int *)arg;

    sem_wait(&resource_sem); // Wait if no resources available
    pthread_mutex_lock(&mutex);

    if (available_resources >= count)
    {
        available_resources -= count;
        printf("Resources Allocated: %d, Available: %d\n", count, available_resources);
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Function to increase resource count
void *increase_count(void *arg)
{
    int count = *(int *)arg;

    pthread_mutex_lock(&mutex);
    available_resources += count;
    printf("Resources Released: %d, Available: %d\n", count, available_resources);
    pthread_mutex_unlock(&mutex);

    sem_post(&resource_sem); // Signal that resources are available
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;
    int req1 = 3, req2 = 2, req3 = 4;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&resource_sem, 0, MAX_RESOURCES);

    pthread_create(&t1, NULL, decrease_count, &req1);
    pthread_create(&t2, NULL, decrease_count, &req2);
    pthread_create(&t3, NULL, increase_count, &req3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Final Available Resources: %d\n", available_resources);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&resource_sem);

    return 0;
}
