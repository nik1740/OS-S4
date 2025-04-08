#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid, AT, BT, CT, TAT, WT;
    bool completed;
};

// Function to find the process with the shortest burst time among available processes
int findShortestJob(struct Process P[], int n, int currentTime) {
    int minBT = 9999, shortestIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!P[i].completed && P[i].AT <= currentTime && P[i].BT < minBT) {
            minBT = P[i].BT;
            shortestIndex = i;
        }
    }
    return shortestIndex;
}

void SJF(struct Process P[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int index = findShortestJob(P, n, currentTime);
        
        if (index == -1) {
            currentTime++;  // Idle time handling
        } else {
            // Update completion time
            currentTime += P[index].BT;
            P[index].CT = currentTime;
            P[index].TAT = P[index].CT - P[index].AT;
            P[index].WT = P[index].TAT - P[index].BT;
            P[index].completed = true;
            
            totalWT += P[index].WT;
            totalTAT += P[index].TAT;
            completed++;
        }
    }

    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, P[i].AT, P[i].BT, P[i].CT, P[i].TAT, P[i].WT);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process P[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &P[i].AT);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &P[i].BT);
        P[i].pid = i + 1;
        P[i].completed = false;
    }

    SJF(P, n);
    return 0;
}
