#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct process
{
    int pid, at, bt, ct, tat, wt, done, remt;
} Pr;

int main()
{
    printf("Enter the no of processes: ");
    int n;
    scanf("%d", &n);

    Pr p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter the at and bt of pid %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remt= p[i].bt;
        p[i].done = 0;
    }

    int time = 0;
    int comp = 0;
    while (comp < n){
        int minRem = INT_MAX;
        int idx = -1;

        // If process has arrived
        for (int i = 0; i < n; i++){
            if (!p[i].done && p[i].at <= time){
                if (p[i].remt < minRem){
                    minRem = p[i].remt;
                    idx = i;
                }
                else if (p[i].remt == minRem){
                    if (p[i].at < p[idx].at || (p[i].at < p[idx].at && p[i].pid < p[idx].pid))
                        idx = i;
                }
            }
        }

        // If process not arrived
        if (idx == -1)
        {
            time++;
            continue;
        }

        p[idx].remt--;
        time++;

        // Do calc
        if (p[idx].remt == 0)
        {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].done = 1;
            comp++;
        }
    }

    float stat=0;
    float swt=0;
    for (int i = 0; i < n; i++){
        stat+= p[i].tat;
        swt+= p[i].wt;
    }
    
    printf("AvgTat: %.2f\n", stat/n);
    printf("Avgswt: %.2f\n", swt/n);
    return 0;
}