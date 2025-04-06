#include <stdio.h>
#include <string.h>
void firstFit(int blockSize[], int m, int processSize[], int n) {
int allocation[n];
memset(allocation, -1, sizeof(allocation));
for (int i = 0; i < n; i++) {
for (int j = 0; j < m; j++) {
if (blockSize[j] >= processSize[i]) {
allocation[i] = j;
blockSize[j] -= processSize[i];
break;
}
}
}
printf("\nProcess No.\tProcess Size\tBlock no.\n");
for (int i = 0; i < n; i++) {
printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
if (allocation[i] != -1)
printf("%d", allocation[i] + 1);
else
printf("Not Allocated");
printf("\n");
}
 printf("Free Blocks\n");
for (int i = 0; i < m; i++) printf("%d->", blockSize[i]);
}
int main() {
int m, n;
printf("Enter the number of memory blocks: ");
scanf("%d", &m);
int blockSize[m];
printf("Enter the sizes of memory blocks:\n");
for (int i = 0; i < m; i++) {
scanf("%d", &blockSize[i]);
}
printf("Enter the number of processes: ");
scanf("%d", &n);
int processSize[n];
printf("Enter the sizes of processes:\n");
for (int i = 0; i < n; i++) {
scanf("%d", &processSize[i]);
}
firstFit(blockSize, m, processSize, n);
return 0;
}
