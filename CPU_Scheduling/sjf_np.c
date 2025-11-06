#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int ct;    // Completion Time
    int wt;    // Waiting Time
    int tat;   // Turnaround Time
    int done;  // Flag to mark completion
} Pr;

int main() {
    int n, i, completed = 0, time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Pr p[n];

    // Input process details
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].done = 0;
    }

    // Scheduling loop
    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        // Find process with shortest BT among those that have arrived
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
                else if (p[i].bt == minBT) {
                    // Tie-breaker: earlier arrival time
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                    // If AT also same → smaller PID
                    else if (p[i].at == p[idx].at && p[i].pid < p[idx].pid) {
                        idx = i;
                    }
                }
            }
        }

        // If no process has arrived, jump time to the earliest arrival
        if (idx == -1) {
            int earliest = 1e9;
            for (i = 0; i < n; i++) {
                if (!p[i].done && p[i].at < earliest) {
                    earliest = p[i].at;
                }
            }
            time = earliest;
            continue;
        }

        // Execute selected process
        p[idx].ct = time + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        time = p[idx].ct;
        p[idx].done = 1;
        completed++;
    }

    // Output table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Calculate averages
    float avgTAT = 0, avgWT = 0;
    for (i = 0; i < n; i++) {
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
    }
    avgTAT /= n;
    avgWT /= n;

    printf("\nAverage Turnaround Time = %.2f", avgTAT);
    printf("\nAverage Waiting Time = %.2f\n", avgWT);

    return 0;
}
