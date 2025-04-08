#include <stdio.h>

struct Process {
    int pid;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int remaining_BT;
};

void roundRobin(struct Process P[], int n, int timeQuantum) {
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int index = queue[front++];
        if (P[index].remaining_BT > timeQuantum) {
            time += timeQuantum;
            P[index].remaining_BT -= timeQuantum;
        } else {
            time += P[index].remaining_BT;
            P[index].remaining_BT = 0;
            P[index].CT = time;
            P[index].TAT = P[index].CT - P[index].AT;
            P[index].WT = P[index].TAT - P[index].BT;
            completed++;
        }
        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && P[i].AT <= time && P[i].remaining_BT > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        
        if (P[index].remaining_BT > 0) {
            queue[rear++] = index;
        }
        
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (P[i].remaining_BT > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    int n, timeQuantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process P[n];
    
    for (int i = 0; i < n; i++) {
        P[i].pid = i + 1;
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &P[i].AT);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &P[i].BT);
        P[i].remaining_BT = P[i].BT;
    }
    
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);
    
    roundRobin(P, n, timeQuantum);
    
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", P[i].pid, P[i].AT, P[i].BT, P[i].CT, P[i].TAT, P[i].WT);
    }
    
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += P[i].TAT;
        avgWT += P[i].WT;
    }
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);
    printf("Average Waiting Time: %.2f\n", avgWT / n);
    
    return 0;
}
