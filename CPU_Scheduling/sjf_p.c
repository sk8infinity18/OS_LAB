#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt;
    int remaining; // remaining burst time (for preemptive)
    int done;      // optional flag
} Pr;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Pr p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining = p[i].bt;
        p[i].done = 0;
    }

    int completed = 0, time = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;
        int minRem = INT_MAX;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].remaining < minRem) {
                    minRem = p[i].remaining;
                    idx = i;
                }
                else if (p[i].remaining == minRem) {
                    if (p[i].at < p[idx].at) idx = i;
                    else if (p[i].at == p[idx].at && p[i].pid < p[idx].pid) idx = i;
                }
            }
        }

        // If no process has arrived, move time forward
        if (idx == -1) {
            time++;
            continue;
        }

        // Run the chosen process for 1 unit
        p[idx].remaining--;
        time++;

        // If the process is finished
        if (p[idx].remaining == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;

            totalTAT += p[idx].tat;
            totalWT += p[idx].wt;
            completed++;
        }
    }

    // Print table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT  = %.2f\n", totalWT / n);

    return 0;
}
