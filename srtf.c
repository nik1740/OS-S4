#include <stdio.h>
#include <stdbool.h>
struct Process{
    int pid,AT,BT,CT,RT,TAT,WT;
    bool completed;
};

int CurrentTime=0;

int findShortest(struct Process P[],int n){
    int i,st=-1;
    int minRT=999;
    for(i=0;i<n;i++){
        if(!P[i].completed && P[i].AT<=CurrentTime && P[i].RT<minRT){
            minRT=P[i].RT;
            st=i;
            
        }
    }
    return st;
}

void SJF(struct Process P[],int n){
    int completed=0,index;
    float totalWT=0,totalTAT=0;
    for(int i=0;i<n;i++){
        P[i].RT=P[i].BT;
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    while(completed<n){
        index=findShortest(P,n);
        if(index!=-1){
            P[index].RT--;
            CurrentTime++;
            if(P[index].RT==0){
                P[index].CT=CurrentTime;
                P[index].TAT=P[index].CT-P[index].AT;
                P[index].WT=P[index].TAT-P[index].BT;
                P[index].completed=true;
                totalWT += P[index].WT;
                totalTAT += P[index].TAT;
                completed++;
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", index, P[index].AT, P[index].BT, P[index].CT, P[index].TAT, P[index].WT);

            }
        }else{

            CurrentTime++;
            

            
        } 
        
    }
    
    
       
    

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

void main(){
   
    int n,i;
    printf("Enter the number of processes:\n");
    scanf("%d",&n); 
    struct Process P[n];   
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &P[i].AT);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &P[i].BT);
        P[i].pid = i + 1;
        P[i].completed = false;
    }
    SJF(P,n);
    printf(",,,,swdds");
}