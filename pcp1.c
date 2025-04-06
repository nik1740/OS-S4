#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep/usleep

#define BUFFER_SIZE 5
#define MAX_ITEMS 10  // Maximum number of items to produce/consume

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int items_produced = 0;
int items_consumed = 0;

void *producer(void *arg) {
    int item = 1;
    while (items_produced < MAX_ITEMS) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer: Produced item %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;
        items_produced++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        usleep(500000);  // 0.5 second delay
    }
    printf("Producer finished producing %d items\n", MAX_ITEMS);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (items_consumed < MAX_ITEMS) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer: Consumed item %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        items_consumed++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        usleep(500000);  // 0.5 second delay
    }
    printf("Consumer finished consuming %d items\n", MAX_ITEMS);
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores and mutex
    if (sem_init(&empty, 0, BUFFER_SIZE) != 0) {
        perror("sem_init empty failed");
        return 1;
    }
    if (sem_init(&full, 0, 0) != 0) {
        perror("sem_init full failed");
        sem_destroy(&empty);
        return 1;
    }
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("mutex_init failed");
        sem_destroy(&empty);
        sem_destroy(&full);
        return 1;
    }

    // Create threads
    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0) {
        perror("pthread_create producer failed");
        return 1;
    }
    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        perror("pthread_create consumer failed");
        return 1;
    }

    // Wait for threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Program completed successfully\n");
    return 0;
}
