#include<stdio.h> 
#include<stdlib.h>
typedef struct process{
    int pid, at, bt, ct,tat, wt;
}Pr;

int main(){
    
    // Get no of processes and their at bt
    printf("Enter no of processes: ");
    int n;
    scanf("%d", &n);

    Pr p[n];

    for (int i = 0; i < n; i++){
        p[i].pid= i+1;
        printf("Enter the at and bt of pid %d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    
    // Sort them according to AT, if tie pid

    for (int i = 0; i < n-1; i++){
        for (int j=1; j < n-i; j++){
            if (p[j-1].at>p[j].at || (p[j-1].at==p[j].at && p[j-1].pid> p[j].pid)){
                
                Pr temp= p[j-1];
                p[j-1]= p[j];
                p[j]= temp;
            }
        }
    }
    
    // Calculate CT,TAT, WT

    int time=0;

    for (int i = 0; i < n; i++){
        if (time< p[i].at){
            time= p[i].at;
        }
        
        p[i].ct= time + p[i].bt;
        p[i].tat= p[i].ct - p[i].at;
        p[i].wt= p[i].tat - p[i].bt;
        time= p[i].ct;
    }
    
    // Calculate Avg tat and wt

    float stat=0;
    float swt=0;

    for (int i = 0; i < n; i++){
        stat += p[i].tat;
        swt += p[i].wt;
    }
    
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("Avg TAT: %.2f\n", stat/n);
    printf("Avg WT: %.2f\n", swt/n);
    return 0;
}