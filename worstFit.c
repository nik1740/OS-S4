#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int *allocation = (int *)malloc(n * sizeof(int));
    if (!allocation) {
        printf("Memory allocation failed for allocation array.\n");
        return;
    }

    memset(allocation, -1, n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int wstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (wstIdx == -1 || blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }
        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1); // +1 to make it 1-based index
        else
            printf("Not Allocated");
        printf("\n");
    }

    printf("\nFree Blocks\n");
    for (int i = 0; i < m; i++)
        printf("%d -> ", blockSize[i]);

    printf("\n");

    free(allocation);
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    if (m <= 0) {
        printf("Number of blocks should be greater than 0.\n");
        return 1;
    }

    int *blockSize = (int *)malloc(m * sizeof(int));
    if (!blockSize) {
        printf("Memory allocation failed for blockSize.\n");
        return 1;
    }

    printf("Enter sizes of %d memory blocks:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Number of processes should be greater than 0.\n");
        free(blockSize);
        return 1;
    }

    int *processSize = (int *)malloc(n * sizeof(int));
    if (!processSize) {
        printf("Memory allocation failed for processSize.\n");
        free(blockSize);
        return 1;
    }

    printf("Enter sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    worstFit(blockSize, m, processSize, n);

    free(blockSize);
    free(processSize);
    return 0;
}
