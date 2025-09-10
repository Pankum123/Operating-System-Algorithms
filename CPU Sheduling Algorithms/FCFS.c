#include<stdio.h>
#define MAX 20

struct FCFS{
    int pid,at,bt,ct,tat,wt;
};

struct FCFS arr[MAX];

void Calculate(int n){
    // sorting -> Arrival time
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j].at > arr[j+1].at || (arr[j].at == arr[j + 1].at && arr[j].pid > arr[j + 1].pid) ){
                struct FCFS temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    // calculate CT, TAT and WT
    for(int i=0;i<n;i++){
        if(i == 0){
            arr[i].ct = arr[i].at + arr[i].bt;   // first process always completes at AT + BT
        } 
        else {
            if(arr[i].at > arr[i-1].ct){
                arr[i].ct = arr[i].at + arr[i].bt;   // CPU idle time
            } else {
                arr[i].ct = arr[i-1].ct + arr[i].bt; // continuous execution
            }
        }

        arr[i].tat = arr[i].ct - arr[i].at;   
        arr[i].wt  = arr[i].tat - arr[i].bt;  
    }
    
}


int main(){
    int n;
    printf("Enter no of process : ");
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        // printf("Enter Process id, Arrival Time and Burst Time :\n");
        scanf("%d%d%d",&arr[i].pid,&arr[i].at,&arr[i].bt);
    }
    

    Calculate(n);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i].pid, arr[i].at, arr[i].bt,
               arr[i].ct, arr[i].tat, arr[i].wt);
    }
   
    printf("\n");

    float sumTAT  = 0;
    float sumWT  = 0;
    for(int i=0;i<n;i++){
        sumTAT += arr[i].tat;
        sumWT += arr[i].wt;
    }
    printf("total TAT = %.2f & avg TAT = %.2f\n",sumTAT,sumTAT/n);
    printf("total WT = %.2f & avg WT = %.2f",sumWT,sumWT/n);


    return 0;
}