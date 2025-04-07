#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // buffer size
#define PRODUCE_ITEMS 10

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;   // counts empty slots
sem_t full;    // counts filled slots
pthread_mutex_t mutex;

void* producer(void* arg)
{
    for (int i = 0; i < PRODUCE_ITEMS; i++)
    {
        int item = rand() % 100; // produce an item
        sem_wait(&empty);        // wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);         // signal that buffer has an item

        sleep(1); // simulate time to produce
    }
    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    for (int i = 0; i < PRODUCE_ITEMS; i++)
    {
        sem_wait(&full);         // wait for available item
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);        // signal that a slot is free

        sleep(1); // simulate time to consume
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}