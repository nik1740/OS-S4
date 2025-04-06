#include <stdio.h>
#define MAX 10

int max[MAX][MAX],alloc[MAX][MAX],need[MAX][MAX],avail[MAX];
int finished[MAX],Safeseq[MAX];
int p,r;

// Function to print matrices in a formatted way
void printMatrices() {
    int i, j;
    
    printf("\nALLOCATION MATRIX:\n");
    printf("Process\\Resource ");
    for(j = 0; j < r; j++)
        printf("R%d ", j);
    printf("\n");
    for(i = 0; i < p; i++) {
        printf("P%d\t\t", i);
        for(j = 0; j < r; j++) {
            printf("%d  ", alloc[i][j]);
        }
        printf("\n");
    }

    printf("\nMAX MATRIX:\n");
    printf("Process\\Resource ");
    for(j = 0; j < r; j++)
        printf("R%d ", j);
    printf("\n");
    for(i = 0; i < p; i++) {
        printf("P%d\t\t", i);
        for(j = 0; j < r; j++) {
            printf("%d  ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nNEED MATRIX:\n");
    printf("Process\\Resource ");
    for(j = 0; j < r; j++)
        printf("R%d ", j);
    printf("\n");
    for(i = 0; i < p; i++) {
        printf("P%d\t\t", i);
        for(j = 0; j < r; j++) {
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }

    printf("\nAVAILABLE RESOURCES:\n");
    for(j = 0; j < r; j++)
        printf("R%d: %d  ", j, avail[j]);
    printf("\n");
}

int canExec(int i){
    int j;
    for(j=0;j<r;j++){
       if(avail[j]<need[i][j])
            return 0;
    }
            return 1;
}

int check(){
    int i,j,count=0;
    for (int i = 0; i < p; i++)
        finished[i] = 0;
    while(count<p){
        int found=0;
        for(i=0;i<p;i++){
            if(!finished[i] && canExec(i)){
                for(j=0;j<r;j++){
                    avail[j]+=alloc[i][j];
                }
                finished[i]=1;
                Safeseq[count++]=i;
                found=1;
            }           
        } if(!found)
        return 0;
    }
   

    return 1;
}


int main(){
    int i,j;
    printf("Enter the number of processes:");
    scanf("%d",&p);
    printf("Enter the number of resources:");
    scanf("%d",&r);
    printf("\nENTER THE MAX MATRIX\n");
    for(i=0;i<p;i++){
        printf("For Process P%d: ", i);
        for(j=0;j<r;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nENTER THE ALLOCATION MATRIX\n");
    for(i=0;i<p;i++){
        printf("For Process P%d: ", i);
        for(j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("\nENTER THE AVAILABLE RESOURCES\n");
    for(i=0;i<r;i++){
        printf("Resource R%d: ", i);
        scanf("%d",&avail[i]);
    }
    for(i=0;i<p;i++){
        for(j=0;j<r;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    // Print all matrices
    printMatrices();

    if(!check())
        printf("\nSystem is NOT in safe state\n");
    else {
        printf("\nSystem is in safe state\n");
        printf("Safe sequence: ");
        for(int l=0;l<p;l++){
            printf("P%d ",Safeseq[l]);
        }
        printf("\n");
    }

    
}

