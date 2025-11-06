#include<stdio.h> 
#include<stdlib.h>
int p,r;
int max[10][10], alloc[10][10], need[10][10];
int avail[10];
int finish[10];
int safe[10];

int isSafe(){
    int work[10];
    
    for (int i = 0; i < r; i++){
        work[i]= avail[i];
    }

    for (int i = 0; i < p; i++){
        finish[i]= 0;
    }

    int count=0;

    while (count<p){
        int found=0;

        for (int i = 0; i < p; i++){
            int flag=0;

            if (!finish[i]){

                //Check if its eligible
                for (int j = 0; j < r; j++){
                    if (need[i][j]>work[j]){
                        flag=1;
                        break;
                    }
                }
                
                // if yes
                if (!flag){
                    for (int k = 0; k < r; k++){
                        work[k]+= alloc[i][k];
                    }
                    
                    safe[count++]= i;
                    finish[i]=1;
                    found=1;
                }
                
            }
        }
            
        if (!found)
        break;
    }
    
    // Check if all the processes processed or not
    if (count==p){
        printf("Safe Sequence: ");
        for (int i = 0; i < count; i++){
        printf("P%d ", safe[i]);
        }
        return 1;
    }else{
        printf("System in deadlock\n");
        return 0;
    }
    
}

void resourceReq(){
    int pid, req[10];

    printf("Enter the pid making request : ");
    scanf("%d", &pid);

    printf("Enter the resource request: ");
    for (int i = 0; i < r; i++){
        scanf("%d" , &req[i]);
    }
    
    // Check need>= req and avail>= req

    for (int i = 0; i < r; i++){
        if (req[i]> need[pid][i] || req[i]> avail[i]){
            printf("Can't be done\n");
            return;
        }
    }

    // pretend allocation

    for (int i = 0; i < r; i++){
        alloc[pid][i]+= req[i];
        need[pid][i]-= req[i];
        avail[i]-= req[i];
    }
    
    // Start bankers
    if (isSafe()){
        printf("System in safe state!\n");
    }else{
        printf("System in unsafe state!\n");

        // rollback changes
        for (int i = 0; i < r; i++){
        alloc[pid][i]-= req[i];
        need[pid][i]+= req[i];
        avail[i]+= req[i];
    }
    }
}

int main(){
    
    printf("Enter no of processes and resources: ");
    scanf("%d %d", &p, &r);

    printf("Enter allocation matrix: ");
    for (int i = 0; i < p; i++){
        for (int j = 0; j < r; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter max matrix: ");
    for (int i = 0; i < p; i++){
        for (int j = 0; j < r; j++){
            scanf("%d", &max[i][j]);
        }
    }

    // Calc need matrix
    for (int i = 0; i < p; i++){
        for (int j = 0; j < r; j++){
            need[i][j]= max[i][j] - alloc[i][j];
        }
    }

    printf("Enter available resources: ");
    for (int i = 0; i < r; i++){
        scanf("%d", &avail[i]);
    }

    while (1){
    printf("Enter choice: ");
    int ch;
    scanf("%d", &ch);
        switch (ch){
        case 1:
            isSafe();
            break;
        
        case 2:
            resourceReq();
            break;

        case 3:
            printf("Exited!");
            break;
        default:
            break;
        }
    }
    return 0;
}

// Enter no of processes and resources: 5 3
// Enter allocation matrix: 0 1 0 2 0 0 3 0 2 2 1 1 0 0 2
// Enter max matrix: 7 5 3 3 2 2 9 0 2 4 2 2 5 3 3

// Enter allocation matrix: 2 0 0 1 3 1 2 1 2 1 0 3 1 3 1 2 1 4 3 2 
// Enter max matrix: 4 2 1 2 5 2 5 2 2 3 1 6 1 4 2 4 3 6 6 5