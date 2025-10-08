#include <stdio.h>
#include <limits.h>
#define MAX 20

struct Process {
    int pid,at,bt,pr,ct,tat,wt;
    int done;
};

struct Process arr[MAX];

void Calculate(int n) {
    int completed = 0, curr = 0;
    int copybt[n];

    for(int i=0; i<n; i++) {
        copybt[i] = arr[i].bt;
        arr[i].done = 0;
    }

    while(completed < n) {
        int idx = -1;
        int high_pr = INT_MIN;

        // Find highest priority process available at current time
        for(int i=0; i<n; i++) {
            if(!arr[i].done && arr[i].at <= curr) {
                if(idx == -1 || arr[i].pr > high_pr || 
                   (arr[i].pr == high_pr && arr[i].at < arr[idx].at) ||
                   (arr[i].pr == high_pr && arr[i].at == arr[idx].at && arr[i].pid < arr[idx].pid)) {
                    high_pr = arr[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            curr++; // No process is available, increment time
        } else {
            copybt[idx]--;
            curr++;

            if(copybt[idx] == 0) { // Process finished
                arr[idx].done = 1;
                arr[idx].ct = curr;
                arr[idx].tat = arr[idx].ct - arr[idx].at;
                arr[idx].wt = arr[idx].tat - arr[idx].bt;
                completed++;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter no of process : ");
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        // printf("Enter Process priority,id, Arrival Time and Burst Time :\n");
        scanf("%d%d%d%d",&arr[i].pr,&arr[i].pid,&arr[i].at,&arr[i].bt);
        arr[i].done = 0;
    }
    

    Calculate(n);

    printf("\nPR\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i].pr, arr[i].pid, arr[i].at, arr[i].bt,
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
