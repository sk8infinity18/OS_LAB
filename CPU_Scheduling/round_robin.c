#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

int main() {
    int n, i, time = 0, completed = 0, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (i = 0; i < n; i++) {
        printf("Enter PID, arrival time, burst time for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int queue[100]; // simple queue
    int front = 0, rear = 0;
    bool in_queue[n]; // track if process is in queue

    for (i = 0; i < n; i++) in_queue[i] = false;

    // Enqueue the first process(es) that have arrived at time 0
    for (i = 0; i < n; i++) {
        if (p[i].arrival_time <= time && !in_queue[i]) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }

    while (completed < n) {
        if (front == rear) { // queue empty, advance time
            time++;
            for (i = 0; i < n; i++) {
                if (p[i].arrival_time <= time && !in_queue[i] && p[i].remaining_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int exec_time = (p[idx].remaining_time > quantum) ? quantum : p[idx].remaining_time;
        printf("Time %d -> %d: Process %d executing\n", time, time + exec_time, p[idx].pid);
        time += exec_time;
        p[idx].remaining_time -= exec_time;

        // Enqueue newly arrived processes during this time slice
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !in_queue[i] && p[i].remaining_time > 0) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }

        if (p[idx].remaining_time > 0) {
            queue[rear++] = idx; // re-add process if not finished
        } else {
            p[idx].turnaround_time = time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            completed++;
        }
    }

    printf("\nPID\tWaiting Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", p[i].pid, p[i].waiting_time, p[i].turnaround_time, p[i].waiting_time);
    }
    
    float stat=0;
    float swt=0;

    for (int i = 0; i < n; i++){
        stat+= p[i].turnaround_time;
        swt+=p[i].waiting_time;
    }
    
    printf("AvgTat: %.2f\n", stat/n);
    printf("AvgWt: %.2f\n", swt/n);

    return 0;
}

