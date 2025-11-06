#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ---------- Comparator for qsort ----------
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void printSequence(int seq[], int n) {
    printf("\nOrder of Head Movement: ");
    for (int i = 0; i < n; i++) printf("%d ", seq[i]);
    printf("\n");
}

// ---------- FCFS ----------
void FCFS(int req[], int n, int head) {
    int total = 0;
    printf("\n--- First Come First Serve (FCFS) ---");
    total += abs(req[0] - head);
    for (int i = 1; i < n; i++)
        total += abs(req[i] - req[i - 1]);
    printSequence(req, n);
    printf("Total Head Movement: %d\n", total);
}

// ---------- SSTF ----------
void SSTF(int req[], int n, int head) {
    int done[n], seq[n], count = 0, total = 0, curr = head;
    for (int i = 0; i < n; i++) done[i] = 0;

    while (count < n) {
        int min = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && abs(req[i] - curr) < min) {
                min = abs(req[i] - curr);
                idx = i;
            }
        }
        done[idx] = 1;
        total += abs(req[idx] - curr);
        curr = req[idx];
        seq[count++] = curr;
    }

    printf("\n--- Shortest Seek Time First (SSTF) ---");
    printSequence(seq, n);
    printf("Total Head Movement: %d\n", total);
}

// ---------- SCAN ----------
void SCAN(int req[], int n, int head, int disk_size) {
    int direction;
    printf("Enter direction (0 = Left, 1 = Right): ");
    scanf("%d", &direction);

    int arr[n + 2];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    arr[n] = 0;
    arr[n + 1] = disk_size - 1;
    int size = n + 2;

    qsort(arr, size, sizeof(int), compare);

    int pos = 0;
    for (int i = 0; i < size; i++)
        if (head < arr[i]) { pos = i; break; }

    int seq[size], count = 0, total = 0;

    printf("\n--- SCAN (Elevator) ---");
    if (direction == 1) {
        for (int i = pos; i < size; i++) seq[count++] = arr[i];
        for (int i = pos - 1; i >= 0; i--) seq[count++] = arr[i];
    } else {
        for (int i = pos - 1; i >= 0; i--) seq[count++] = arr[i];
        for (int i = pos; i < size; i++) seq[count++] = arr[i];
    }

    total += abs(seq[0] - head);
    for (int i = 1; i < count; i++)
        total += abs(seq[i] - seq[i - 1]);

    printSequence(seq, count);
    printf("Total Head Movement: %d\n", total);
}

// ---------- LOOK ----------
void LOOK(int req[], int n, int head) {
    int direction;
    printf("Enter direction (0 = Left, 1 = Right): ");
    scanf("%d", &direction);

    int arr[n];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    qsort(arr, n, sizeof(int), compare);

    int pos = 0;
    for (int i = 0; i < n; i++)
        if (head < arr[i]) { pos = i; break; }

    int seq[n], count = 0, total = 0;

    printf("\n--- LOOK (Bidirectional) ---");
    if (direction == 1) {
        for (int i = pos; i < n; i++) seq[count++] = arr[i];
        for (int i = pos - 1; i >= 0; i--) seq[count++] = arr[i];
    } else {
        for (int i = pos - 1; i >= 0; i--) seq[count++] = arr[i];
        for (int i = pos; i < n; i++) seq[count++] = arr[i];
    }

    total += abs(seq[0] - head);
    for (int i = 1; i < count; i++)
        total += abs(seq[i] - seq[i - 1]);

    printSequence(seq, count);
    printf("Total Head Movement: %d\n", total);
}

// ---------- C-SCAN ----------
void CSCAN(int req[], int n, int head, int disk_size) {
    int direction;
    printf("Enter direction (0 = Left, 1 = Right): ");
    scanf("%d", &direction);

    int arr[n + 2];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    arr[n] = 0;
    arr[n + 1] = disk_size - 1;
    int size = n + 2;

    qsort(arr, size, sizeof(int), compare);

    int pos = 0;
    for (int i = 0; i < size; i++)
        if (head < arr[i]) { pos = i; break; }

    int seq[size], count = 0, total = 0;

    printf("\n--- Circular SCAN (C-SCAN) ---");
    if (direction == 1) { // right direction
        for (int i = pos; i < size; i++) seq[count++] = arr[i];
        for (int i = 0; i < pos; i++) seq[count++] = arr[i];
    } else { // left direction
        for (int i = pos - 1; i >= 0; i--) seq[count++] = arr[i];
        for (int i = size - 1; i >= pos; i--) seq[count++] = arr[i];
    }

    total += abs(seq[0] - head);
    for (int i = 1; i < count; i++)
        total += abs(seq[i] - seq[i - 1]);

    total -= (disk_size - 1); // ignore jump distance

    printSequence(seq, count);
    printf("Total Head Movement: %d\n", total);
}

// ---------- C-LOOK ----------
void CLOOK(int req[], int n, int head) {
    int direction;
    printf("Enter direction (0 = Left, 1 = Right): ");
    scanf("%d", &direction);

    int arr[n];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    qsort(arr, n, sizeof(int), compare);

    int pos = 0;
    for (int i = 0; i < n; i++)
        if (head < arr[i]) { pos = i; break; }

    int seq[n], count = 0, total = 0;

    printf("\n--- Circular LOOK (C-LOOK) ---");
    if (direction == 1) {
        for (int i = pos; i < n; i++) seq[count++] = arr[i];
        for (int i = 0; i < pos; i++) seq[count++] = arr[i];
    } else {
        for (int i = pos - 1; i >= 0; i--) seq[count++] = arr[i];
        for (int i = n - 1; i >= pos; i--) seq[count++] = arr[i];
    }

    total += abs(seq[0] - head);
    for (int i = 1; i < count; i++)
        total += abs(seq[i] - seq[i - 1]);

    printSequence(seq, count);
    printf("Total Head Movement: %d\n", total);
}

// ---------- MAIN ----------
int main() {
    int n, head, disk_size, choice;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (e.g. 200 for 0-199): ");
    scanf("%d", &disk_size);

    do {
        printf("\n\n===== DISK SCHEDULING MENU =====\n");
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. LOOK\n5. C-SCAN\n6. C-LOOK\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: FCFS(req, n, head); break;
            case 2: SSTF(req, n, head); break;
            case 3: SCAN(req, n, head, disk_size); break;
            case 4: LOOK(req, n, head); break;
            case 5: CSCAN(req, n, head, disk_size); break;
            case 6: CLOOK(req, n, head); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
