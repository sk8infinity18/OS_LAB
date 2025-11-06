#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    int status;
    pid_t pid = fork();

    if (pid==0)
    {
        printf("Child process executing..with PID %d and PPID %d \n", getpid(), getppid());
        printf("Executing child tasks..\n");
        // abort(); --> To abruptly terminate the child process (SEE NOTES)
        sleep(3);
        printf("Child done..\n");
    }else{
        printf("Parent process executing..with PID %d and PPID %d \n", getpid(), getppid());
        printf("Waiting for child tasks..\n");
        wait(&status);
        sleep(2);
        if (WIFEXITED(status)){
            printf("Child exited normally with status code %d\n",  WEXITSTATUS(status));
        }else{
            printf("Child exited abnormally\n");
        }
        
        printf("Parent now exiting..\n");
    }
    
    return 0;
}

// abort() immediately terminates the process.
// It generates a SIGABRT signal, which usually causes the program to crash and may produce a core dump 
// (depending on system settings).
// This is considered abnormal termination — unlike exit(), which is normal.