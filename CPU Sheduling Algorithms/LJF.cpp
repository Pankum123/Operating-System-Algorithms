#include<stdio.h>
#include<limits.h>
#define MAX 20

struct LJF{
    int pid,at,bt,ct,tat,wt;
    int done;
};

struct LJF arr[MAX];

void Calculate(int n) {
    int completed = 0, curr = 0;

    while (completed < n) {
        int idx = -1;
        int max_bt = -1;

        // Check the ready queue -> choose the process with the longest burst time
        for (int i = 0; i < n; i++) {
            if (!arr[i].done && arr[i].at <= curr) {
                if (idx == -1 || arr[i].bt > max_bt || 
                   (arr[i].bt == max_bt && arr[i].at < arr[idx].at) || 
                   (arr[i].bt == max_bt && arr[i].at == arr[idx].at && arr[i].pid < arr[idx].pid)) {
                    max_bt = arr[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process has arrived yet -> CPU is idle
            curr++;
        } else {
            // Found a process -> calculate its times
            arr[idx].ct = curr + arr[idx].bt;
            arr[idx].tat = arr[idx].ct - arr[idx].at;
            arr[idx].wt  = arr[idx].tat - arr[idx].bt;
            arr[idx].done = 1;

            curr = arr[idx].ct;  // Move current time forward
            completed++;         // Increase count of completed processes
        }
    }
}

int main(){
    int n;
    printf("Enter no of process : ");
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        // printf("Enter Process id, Arrival Time and Burst Time :\n");
        scanf("%d%d%d",&arr[i].pid,&arr[i].at,&arr[i].bt);
        arr[i].done = 0;
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