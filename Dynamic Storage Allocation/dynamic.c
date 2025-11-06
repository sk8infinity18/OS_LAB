#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int size;
    int remaining;
} Hole;

typedef struct {
    int id;
    int size;
    int allocated;   // 1 = allocated, 0 = not allocated
    int hole_id;     // which hole assigned
} Process;

// ---------- Utility to print allocation results ----------
void printResults(Hole *holes, int nh, Process *procs, int np, const char *title) {
    printf("\n--- %s ---\n", title);

    printf("\n%-10s %-6s %-15s %-12s\n", "Process", "Size", "Hole Allocated", "Status");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < np; i++) {
        if (procs[i].allocated)
            printf("%-10d %-6d %-15d %-12s\n", procs[i].id, procs[i].size, procs[i].hole_id, "Allocated");
        else
            printf("%-10d %-6d %-15s %-12s\n", procs[i].id, procs[i].size, "-", "Not Allocated");
    }

    printf("\n%-10s %-15s %-10s\n", "Hole ID", "Original Size", "Remaining");
    printf("---------------------------------------------\n");
    for (int j = 0; j < nh; j++)
        printf("%-10d %-15d %-10d\n", holes[j].id, holes[j].size, holes[j].remaining);
}

// ---------- First Fit ----------
void firstFit(Hole *holes, int nh, Process *procs, int np) {
    for (int i = 0; i < np; i++) {
        procs[i].allocated = 0;
        for (int j = 0; j < nh; j++) {
            if (holes[j].remaining >= procs[i].size) {
                procs[i].allocated = 1;
                procs[i].hole_id = holes[j].id;
                holes[j].remaining -= procs[i].size;
                break;
            }
        }
    }
    printResults(holes, nh, procs, np, "FIRST FIT ALLOCATION");
}

// ---------- Best Fit ----------
void bestFit(Hole *holes, int nh, Process *procs, int np) {
    for (int i = 0; i < np; i++) {
        int bestIndex = -1;
        int minDiff = 99999;

        for (int j = 0; j < nh; j++) {
            if (holes[j].remaining >= procs[i].size) {
                int diff = holes[j].remaining - procs[i].size;
                if (diff < minDiff) {
                    minDiff = diff;
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            procs[i].allocated = 1;
            procs[i].hole_id = holes[bestIndex].id;
            holes[bestIndex].remaining -= procs[i].size;
        } else {
            procs[i].allocated = 0;
        }
    }
    printResults(holes, nh, procs, np, "BEST FIT ALLOCATION");
}

// ---------- Worst Fit ----------
void worstFit(Hole *holes, int nh, Process *procs, int np) {
    for (int i = 0; i < np; i++) {
        int worstIndex = -1;
        int maxDiff = -1;

        for (int j = 0; j < nh; j++) {
            if (holes[j].remaining >= procs[i].size) {
                int diff = holes[j].remaining - procs[i].size;
                if (diff > maxDiff) {
                    maxDiff = diff;
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            procs[i].allocated = 1;
            procs[i].hole_id = holes[worstIndex].id;
            holes[worstIndex].remaining -= procs[i].size;
        } else {
            procs[i].allocated = 0;
        }
    }
    printResults(holes, nh, procs, np, "WORST FIT ALLOCATION");
}

// ---------- Main ----------
int main() {
    int nh, np, choice;
    Hole *holes;
    Process *procs;

    printf("Enter number of holes: ");
    scanf("%d", &nh);
    holes = (Hole *)malloc(nh * sizeof(Hole));
    for (int i = 0; i < nh; i++) {
        holes[i].id = i + 1;
        printf("Enter size of Hole %d: ", i + 1);
        scanf("%d", &holes[i].size);
        holes[i].remaining = holes[i].size;
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &np);
    procs = (Process *)malloc(np * sizeof(Process));
    for (int i = 0; i < np; i++) {
        procs[i].id = i + 1;
        printf("Enter memory required for Process %d: ", i + 1);
        scanf("%d", &procs[i].size);
        procs[i].allocated = 0;
        procs[i].hole_id = -1;
    }

    printf("\nChoose Allocation Strategy:\n");
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n\n Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            firstFit(holes, nh, procs, np);
            break;
        case 2:
            bestFit(holes, nh, procs, np);
            break;
        case 3:
            worstFit(holes, nh, procs, np);
            break;

        default:
            printf("Invalid choice!\n");
    }

    free(holes);
    free(procs);
    return 0;
}
