#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, done;
} Pr;

int main() {
    printf("Enter the no of processes: ");
    int n;
    scanf("%d", &n);

    Pr p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the AT and BT of P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = INT_MAX;  // large number

        // Select process with shortest BT
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                } else if (p[i].bt == minBT) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    } else if (p[i].at == p[idx].at && p[i].pid < p[idx].pid) {
                        idx = i;
                    }
                }
            }
        }

        // If no process has arrived yet
        if (idx == -1) {
            int early = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!p[i].done && p[i].at < early) {
                    early = p[i].at;
                }
            }
            time = early;
            continue;
        }

        // Execute selected process
        p[idx].ct = time + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;
        time = p[idx].ct;  // ✅ update system time
    }

    // Print results
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
    }
    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT  = %.2f\n", avgWT / n);

    return 0;
}
