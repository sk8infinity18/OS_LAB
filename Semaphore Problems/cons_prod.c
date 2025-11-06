#include<stdio.h> 
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

#define CAPACITY 5

int buffer[CAPACITY];
int in=0, out=0;

// Init the semaphores
sem_t empty, full;
sem_t pmutex, cmutex;

// producer
void* producer(void* arg){
    while (1){
        int item= rand()%100;

        // Lock it while entering
        sem_wait(&empty);
        sem_wait(&pmutex);

        buffer[in]= item;
        printf("Producer produced: %d\n", item);
        in =(in+1) % CAPACITY;

        // Unlock it while exiting

        sem_post(&pmutex);
        sem_post(&full);

        sleep(2); //simulate work
    }
}

void* consumer(void* arg){
    while (1){
        
        // Lock it while entering
        sem_wait(&full);
        sem_wait(&cmutex);

        // Consume the item
        int cons= buffer[out];
        printf("Consumer consumes: %d\n", cons);
        out= (out+1)% CAPACITY;

        // Unlock it while exiting

        sem_post(&cmutex);
        sem_post(&empty);

        sleep(1); //simulate work
    }
}


int main(){
    
    // Initialise semaphores
    sem_init(&empty,0, CAPACITY);
    sem_init(&full,0, 0);
    sem_init(&pmutex,0, 1);
    sem_init(&cmutex,0, 1);

    // Create the producer consumer threads
    pthread_t prod,cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Start the threads
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}