#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

int readcount=0;
sem_t mutex, writesem;

void* reader(void* arg){
    
    int id= *((int*)arg);

    while (1){

    // Entry section
    sem_wait(&mutex);
    readcount++;
    if (readcount==1){
        sem_wait(&writesem);
    }

    sem_post(&mutex);

    // Critical section
    printf("Reader %d reading..\n", id);
    sleep(1);

    // Exit
    sem_wait(&mutex);
    readcount--;
    if (readcount==0){
        sem_post(&writesem);
    }
    sem_post(&mutex);

    // Remainder section
    printf("Reader %d finished reading..\n", id);
    sleep(1);
    }

    return NULL;
}

void* writer(void* arg){
    int id= *((int*)arg);

    while (1){
        sem_wait(&writesem);

        printf("Writer %d writing..\n", id);
        sleep(2);

        sem_post(&writesem);

        printf("Writer %d finished writing.. \n", id);
        sleep(2);
    }
    return NULL;
}

int main(){
    
    sem_init(&mutex,0,1);
    sem_init(&writesem,0,1);

    pthread_t rtid[5], wtid[3];
    int rid[5], wid[3];

    for (int i = 0; i < 5; i++){
        rid[i]= i+1;
        pthread_create(&rtid[i], NULL, reader, &rid[i]);
    }

    for (int i = 0; i < 3; i++){
        wid[i]= i+1;
        pthread_create(&wtid[i], NULL, writer, &wid[i]);
    }
    
    // Start the threads

    for (int i = 0; i < 5; i++) pthread_join(rtid[i], NULL);
    for (int i = 0; i < 3; i++) pthread_join(wtid[i], NULL);
    
    return 0;
}