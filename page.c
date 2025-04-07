#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int isInFrames(int frame[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frame[i] == page)
            return 1;
    }
    return 0;
}

void fifo(int pages[], int n, int m) {
    int frame[n];
    int pageFaults = 0, index = 0;

    for (int i = 0; i < n; i++)
        frame[i] = -1;

    for (int i = 0; i < m; i++) {
        if (!isInFrames(frame, n, pages[i])) {
            frame[index] = pages[i];
            index = (index + 1) % n;
            pageFaults++;
        }

        printf("Frame: ");
        for (int j = 0; j < n; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

void lru(int pages[], int n, int m) {
    int frame[n], recent[m];
    int pageFaults = 0;

    for (int i = 0; i < n; i++)
        frame[i] = -1;

    for (int i = 0; i < m; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < n) {
                frame[i] = pages[i];
            } else {
                int least_recent = i, index = -1;
                for (int j = 0; j < n; j++) {
                    int k;
                    for (k = i - 1; k >= 0; k--) {
                        if (pages[k] == frame[j]) {
                            if (k < least_recent) {
                                least_recent = k;
                                index = j;
                            }
                            break;
                        }
                    }
                }
                if (index != -1)
                    frame[index] = pages[i];
            }
            pageFaults++;
        }

        printf("Frame: ");
        for (int j = 0; j < n; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void lfu(int pages[], int n, int m) {
    int frame[n], freq[MAX] = {0};
    int pageFaults = 0;

    for (int i = 0; i < n; i++)
        frame[i] = -1;

    for (int i = 0; i < m; i++) {
        freq[pages[i]]++;

        if (isInFrames(frame, n, pages[i])) {
            // already in frame, no fault
        } else {
            int index = -1;
            for (int j = 0; j < n; j++) {
                if (frame[j] == -1) {
                    index = j;
                    break;
                }
            }

            if (index == -1) {
                // need to replace least frequently used
                int minFreq = INT_MAX;
                int replaceIndex = -1;
                for (int j = 0; j < n; j++) {
                    if (freq[frame[j]] < minFreq) {
                        minFreq = freq[frame[j]];
                        replaceIndex = j;
                    }
                }
                index = replaceIndex;
            }

            frame[index] = pages[i];
            pageFaults++;
        }

        printf("Frame: ");
        for (int j = 0; j < n; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (LFU): %d\n", pageFaults);
}

int main() {
    int pages[MAX], n, m, choice;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    printf("Enter number of pages: ");
    scanf("%d", &m);

    printf("Enter page reference string (space-separated):\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &pages[i]);

    do {
        printf("\nMenu:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. LFU\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, n, m);
                break;
            case 2:
                lru(pages, n, m);
                break;
            case 3:
                lfu(pages, n, m);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
