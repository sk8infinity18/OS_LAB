#include<stdio.h> 
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t dinp[5];

void* dining(void* arg){
    int id= *(int*)arg;

    while (1){
        printf("Philosopher %d is thinking \n", id);
        sleep(2);

        // Pick chposticks
        int left= id;
        int right= (id+1) % 5;

        if (id==4){
            right= id;
            left= (id+1) % 5;
        }

        // Lock
        sem_wait(&dinp[left]);
        sem_wait(&dinp[right]);

        // Start eating
        printf("philosopher %d eating \n", id);
        sleep(2);

        // Unlock after eating
        
        sem_post(&dinp[left]);
        sem_post(&dinp[right]);

        printf("philosopher %d finished eating \n", id);
        
    }
    
}
int main(){
    for (int i = 0; i < 5; i++){
        sem_init(&dinp[i], 0, 1);
    }

    int did[5];
    pthread_t tid[5];
    for (int i = 0; i < 5; i++){
        did[i]=i+1;
        pthread_create(&tid[i], NULL, dining, &did[i]);
    }

    for (int i = 0; i < 5; i++){
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}