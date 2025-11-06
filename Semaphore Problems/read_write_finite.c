#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int readcount = 0;
sem_t mutex, writesem;

// Number of times each reader/writer will execute
#define READER_ITER 3
#define WRITER_ITER 2

void* reader(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < READER_ITER; i++) {
        // Entry section
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&writesem); // First reader locks writers
        }
        sem_post(&mutex);

        // Critical section
        printf("Reader %d reading (iteration %d)...\n", id, i+1);
        fflush(stdout);
        sleep(1);

        // Exit section
        sem_wait(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&writesem); // Last reader releases writers
        }
        sem_post(&mutex);

        // Remainder section
        printf("Reader %d finished reading (iteration %d).\n", id, i+1);
        fflush(stdout);
        sleep(1);
    }

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < WRITER_ITER; i++) {
        // Entry section
        sem_wait(&writesem);

        // Critical section
        printf("Writer %d writing (iteration %d)...\n", id, i+1);
        fflush(stdout);
        sleep(2);

        // Exit section
        sem_post(&writesem);

        // Remainder section
        printf("Writer %d finished writing (iteration %d).\n", id, i+1);
        fflush(stdout);
        sleep(2);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t rtid[5], wtid[3];
    int rid[5], wid[3];

    sem_init(&mutex, 0, 1);
    sem_init(&writesem, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        rid[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &rid[i]);
    }

    // Create writer threads
    for (int i = 0; i < 3; i++) {
        wid[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &wid[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) pthread_join(rtid[i], NULL);
    for (int i = 0; i < 3; i++) pthread_join(wtid[i], NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writesem);

    printf("All readers and writers have finished.\n");
    return 0;
}
