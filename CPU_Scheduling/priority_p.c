#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;
    int remaining_bt;
    int done;
} Pr;

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Priority rule: \n1. Lower number = higher priority (default)\n2. Higher number = higher priority\nEnter choice (1 or 2): ");
    scanf("%d", &choice);

    Pr p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].remaining_bt = p[i].bt;
        p[i].done = 0;
    }

    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int selectedPriority = (choice == 1) ? 1e9 : -1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= currentTime) {
                if ((choice == 1 && p[i].priority < selectedPriority) ||
                    (choice == 2 && p[i].priority > selectedPriority)) {
                    selectedPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == selectedPriority) {
                    // Tie: arrival time (FCFS)
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    } else if (p[i].at == p[idx].at) {
                        // Tie: lower PID
                        if (p[i].pid < p[idx].pid) {
                            idx = i;
                        }
                    }
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            // Run process for 1 unit
            p[idx].remaining_bt--;
            currentTime++;

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;

                p[idx].done = 1;
                completed++;
            }
        }
    }

    // Print results
    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
