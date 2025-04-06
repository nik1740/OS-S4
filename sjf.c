#include<stdio.h>

struct Process {
    int pid;
    int arrivaltime;
    int bursttime;

};

void sortProcesses(struct Process processes[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].bursttime>processes[j+1].bursttime){
                struct Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}



    void calculateTimes(struct Process processes[],int n,int wt[],int tat[]){
        wt[0] = 0;
        tat[0]=processes[0].bursttime;

        for(int i=1;i<n;i++){
            wt[i] = wt[i-1] + processes[i-1].bursttime;
            tat[i] = wt[i] + processes[i].bursttime;
        }
    }

    void calculateAvgTimes(struct Process processes[],int n){
        int wt[n], tat[n];
        calculateTimes(processes,n,wt,tat);
        float avgwt = 0,avgtat=0;
            printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
            for(int i=0;i<n;i++){
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].pid,processes[i].arrivaltime,processes[i].bursttime,wt[i],tat[i]);
                avgwt+=wt[i];
                avgtat+=tat[i];
            }
            printf("\nAverage waiting time: %.2f",avgwt/n);
            printf("\nAverage turnaround time: %.2f",avgtat/n);
            

    }

    int main(){
        int n;
        printf("Enter the number of processes: ");
        scanf("%d",&n);
        struct Process processes[n];
        for(int i=0;i<n;i++){
            printf("Enter the arrival time and burst time for process P%d: ",i+1);
            scanf("%d %d",&processes[i].arrivaltime,&processes[i].bursttime);
            processes[i].pid = i+1;
        }
        sortProcesses(processes,n);
        calculateAvgTimes(processes,n);
        return 0;
        
    }
