#include<stdio.h> 
#include<stdlib.h>
#include<limits.h>
typedef struct process{
    int pid, at,bt, ct,tat,wt,prior,done;
}Pr;

int main(){
    printf("Enter the no of processes: ");
    int n;
    scanf("%d", &n);
    
    Pr p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].prior);
        p[i].done = 0;
    }
    
    int ch;
    printf("Enter your choice: 1(default), 2 (H to H): ");
    scanf("%d", &ch);

    int time=0;
    int comp=0;

    while (comp<n){
        int idx=-1;
        int tsp= (ch==1) ? INT_MAX : INT_MIN;

        for (int i = 0; i < n; i++){
            if (!p[i].done && p[i].at <=time){
                if (ch==1 && p[i].prior< tsp || ch==2 && p[i].prior> tsp){
                    tsp=p[i].prior;
                    idx=i;
                }else if (p[i].prior== tsp){
                    if (p[i].at <p[idx].at || ( p[i].at == p[idx].at && p[i].pid <p[idx].pid ))
                    {
                        idx=i;
                    }
                    
                }
            }
        }

        if (idx==-1){
            time++;
        }else{

            p[idx].ct= time+ p[idx].bt;
            p[idx].tat=  p[idx].ct - p[idx].at;
            p[idx].wt= p[idx].tat- p[idx].bt;
            
            p[idx].done=1;
            time+=p[idx].bt;   //note we are updating cpu clock with bt
            comp++;
        }
    }

    float stat=0;
    float swt=0;
    for (int i = 0; i < n; i++){
        stat+=p[i].tat;
        swt+=p[i].wt;
    }
    
    printf("AvgTat: %.2f\n", stat/n);
    printf("AvgSwt: %.2f\n", swt/n);
    
    return 0;
}