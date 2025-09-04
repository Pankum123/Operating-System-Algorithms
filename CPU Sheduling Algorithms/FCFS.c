#include<stdio.h>
#define MAX 20

struct FCFS{
    int pid,at,bt,ct,tat,wt;
};

struct FCFS arr[MAX];

void Calculate_CT_TAT_WT(int n){
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

    // calculate CT
    arr[0].ct = arr[0].at + arr[0].bt;  // first process completes at AT+BT
    for(int i=1;i<n;i++){
        if(arr[i].at > arr[i-1].ct){
            arr[i].ct = arr[i].at + arr[i].bt; // CPU idle
        } else {
            arr[i].ct = arr[i-1].ct + arr[i].bt; // no idle
        }
    }
    
    for(int i=0;i<n;i++){
        arr[i].tat = arr[i].ct - arr[i].at;     // calculate tat
        arr[i].wt = arr[i].tat - arr[i].bt;     // calculate wt
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
    

    Calculate_CT_TAT_WT(n);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i].pid, arr[i].at, arr[i].bt,
               arr[i].ct, arr[i].tat, arr[i].wt);
    }
   
    printf("\n");

    float sumTAT  = 0;
    float sumCT  = 0;
    for(int i=0;i<n;i++){
        sumTAT += arr[i].tat;
        sumCT += arr[i].wt;
    }
    printf("total TAT = %.2f & avg TAT = %.2f\n",sumTAT,sumTAT/n);
    printf("total CT = %.2f & avg CT = %.2f",sumCT,sumCT/n);


    return 0;
}