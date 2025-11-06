#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Process
{
    int at, bt, ct, tat, wt, remt;
} Pr;

int main()
{
    printf("Enter the no of process: ");
    int n;
    scanf("%d", &n);

    Pr p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter the at and bt of pid %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remt=p[i].bt;
    }

    printf("Enter the time quantum: ");
    int tq;
    scanf("%d", &tq);

    // Make the queues
    int q[1000];
    int f = 0, r = 0;
    bool rq[n];

    int time = 0;
    int completed = 0;

    // Init the bool queue to false
    for (int i = 0; i < n; i++)
        rq[i] = false;

    for (int i = 0; i < n; i++){
        if (!rq[i] && p[i].at <= time){
            q[r++] = i;
            rq[i] = true;
        }
    }

    while (completed < n){
        if (f == r){
            time++;
            for (int i = 0; i < n; i++){
                if (!rq[i] && p[i].at <= time && p[i].remt>0){
                    q[r++] = i;
                    rq[i] = true;
                }
            }
            continue;
        }

        int idx= q[f++];
        int ext= (p[idx].remt> tq) ? tq : p[idx].remt;
        time+=ext;
        p[idx].remt-=ext;

        for (int i = 0; i < n; i++){
            if (!rq[i] && p[i].at <= time && p[i].remt>0){
                q[r++] = i;
                rq[i] = true;
            }
        }

        if (p[idx].remt>0){
            q[r++]= idx;
        }else{
            p[idx].ct=time;
            p[idx].tat= p[idx].ct- p[idx].at;
            p[idx].wt= p[idx].tat- p[idx].bt;
            completed++;
        }
        
    }

    float stat=0;
    float swt=0;

    for (int i = 0; i < n; i++){
        stat+= p[i].tat;
        swt+=p[i].wt;
    }
    
    printf("AvgTat: %.2f\n", stat/n);
    printf("AvgWt: %.2f\n", swt/n);
    return 0;
}