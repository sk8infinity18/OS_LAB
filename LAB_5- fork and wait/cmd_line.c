#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char *argv[]) {

    pid_t pid= fork();
    int status;

    if (pid==0){
    printf("Child process\n");
    // Bubble sort only argv[1..argc-1]
    printf("Sorting...\n");
    sleep(2);
    for (int i = 1; i < argc - 1; i++) {
        for (int j = 2; j < argc - i + 1; j++) {  // j starts at 2, so argv[0] excluded
            if (strcmp(argv[j-1], argv[j]) > 0) {
                char *temp = argv[j-1];
                argv[j-1] = argv[j];
                argv[j] = temp;
            }
        }
    }
    printf("Sorted list (excluding program name): \n");
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    }else{
        printf("Parent process..\n");
        char* arr[argc-1];
        for (int i = 0; i < argc; i++){
            arr[i]= argv[i+1];
        }
        printf("Waiting for child process...\n");
        wait(&status);
        printf("Unsorted list: ");
        for(int i = 0; i < argc-1; i++){
            printf("%s ", arr[i]);
        }
        printf("\n");
        if (WIFEXITED(status)){
             printf("Child exited normally with status code %d\n",  WEXITSTATUS(status));
        }else{
            printf("Child exited abnormally\n");
        }
    }
    return 0;
}
