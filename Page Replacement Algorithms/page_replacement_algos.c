#include <stdio.h>
#include <stdlib.h>

// ---------- FIFO PAGE REPLACEMENT ----------
void fifoPageReplacement(int *pages, int n, int framesCount) {
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int i, j, k, pageFaults = 0, index = 0, found;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");
    printf("Reference String: ");
    for (i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\n\nPage Replacement Process:\n");

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < framesCount; j++)
            if (frames[j] == pages[i]) { found = 1; break; }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % framesCount;
            pageFaults++;
        }

        printf("After page %d → ", pages[i]);
        for (k = 0; k < framesCount; k++)
            (frames[k] == -1) ? printf(" - ") : printf("%2d ", frames[k]);
        printf(found ? "  (Hit)\n" : "  (Fault)\n");
    }

    printf("\nTotal Page Faults (FIFO): %d\n", pageFaults);
    free(frames);
}

// ---------- LRU PAGE REPLACEMENT ----------
int findLRU(int *time, int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
        if (time[i] < min) {
            min = time[i]; 
            pos = i; 
        }

    return pos;
}

void lruPageReplacement(int *pages, int n, int framesCount) {
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int *time = (int *)malloc(framesCount * sizeof(int));
    int count = 0, faults = 0, i, j, found;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n--- LRU Page Replacement ---\n");
    printf("Reference String: ");
    for (i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\n\nPage Replacement Process:\n");

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < framesCount; j++)
            if (frames[j] == pages[i]) {
                time[j] = ++count;
                found = 1; break;
            }

        if (!found) {
            int pos = -1;
            for (j = 0; j < framesCount; j++)
                if (frames[j] == -1) { pos = j; break; }
            if (pos == -1) pos = findLRU(time, framesCount);

            frames[pos] = pages[i];
            time[pos] = ++count;
            faults++;
        }

        printf("After page %d → ", pages[i]);
        for (j = 0; j < framesCount; j++)
            (frames[j] == -1) ? printf(" - ") : printf("%2d ", frames[j]);
        printf(found ? "  (Hit)\n" : "  (Fault)\n");
    }

    printf("\nTotal Page Faults (LRU): %d\n", faults);
    free(frames);
    free(time);
}

// ---------- OPTIMAL PAGE REPLACEMENT ----------
int predict(int *pages, int *frames, int n, int index, int framesCount) {
    int farthest = index, result = -1;
    for (int i = 0; i < framesCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) { farthest = j; result = i; }
                break;
            }
        }
        if (j == n) return i; // not used again
    }
    return (result == -1) ? 0 : result;
}

void optimalPageReplacement(int *pages, int n, int framesCount) {
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int pageFaults = 0, i, j, k, found;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");
    printf("Reference String: ");
    for (i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\n\nPage Replacement Process:\n");

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < framesCount; j++)
            if (frames[j] == pages[i]) {
                found = 1; 
                break; 
            }

        if (!found) {
            int empty = -1;
            for (j = 0; j < framesCount; j++)
                if (frames[j] == -1) { empty = j; break; }

            if (empty != -1) frames[empty] = pages[i];
            else frames[predict(pages, frames, n, i + 1, framesCount)] = pages[i];
            pageFaults++;
        }

        printf("After page %d → ", pages[i]);
        for (k = 0; k < framesCount; k++)
            (frames[k] == -1) ? printf(" - ") : printf("%2d ", frames[k]);
        printf(found ? "  (Hit)\n" : "  (Fault)\n");
    }

    printf("\nTotal Page Faults (Optimal): %d\n", pageFaults);
    free(frames);
}

// ---------- MAIN FUNCTION ----------
int main() {
    int n, framesCount, i, choice;
    int *pages;

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    pages = (int *)malloc(n * sizeof(int));
    printf("Enter the reference string (space-separated): ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    do {
        printf("\n========= PAGE REPLACEMENT MENU =========\n");
        printf("1. FIFO Page Replacement\n");
        printf("2. LRU Page Replacement\n");
        printf("3. Optimal Page Replacement\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fifoPageReplacement(pages, n, framesCount); break;
            case 2: lruPageReplacement(pages, n, framesCount); break;
            case 3: optimalPageReplacement(pages, n, framesCount); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    free(pages);
    return 0;
}
