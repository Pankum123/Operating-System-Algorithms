#include<stdio.h>
#define MAX 20

struct SJF{
    int pid,at,bt,ct,tat,wt;
    int done;
};

struct SJF arr[MAX];

// void Calculate(int n){
   
//     // sorting -> Burst time -> Arrivel Time -> PID
//     for(int i=0;i<n-1;i++){
//         for(int j=0;j<n-i-1;j++){
//             if(arr[j].bt > arr[j+1].bt || (arr[j].bt == arr[j+1].bt && arr[j].at > arr[j+1].at) || (arr[j].at == arr[j + 1].at && arr[j].pid > arr[j + 1].pid) ){
//                 struct SJF temp = arr[j];
//                 arr[j] = arr[j+1];
//                 arr[j+1] = temp;
//             }
//         }
//     }
//     int i = 0;
//     int curr = 0;
//     while(i<=n){
//         if(arr[i].done == 1){
//             i++;
//         }
//         else if(arr[i].at > curr){
//             int minidx = 0;
//             for(int j=i;j<n;j++){
//                 if(arr[j].done !=1 && (arr[j].at < arr[minidx].at || (arr[j].at == arr[minidx].at && arr[j].pid < arr[minidx].pid))) minidx = j;
//             }
//             if(arr[minidx].at > curr){
//                 arr[minidx].ct = arr[minidx].at + arr[minidx].bt; // CPU idle
//             } else {
//                 arr[minidx].ct = curr + arr[minidx].bt; // no idle
//             }
//             curr = arr[minidx].ct;
//             arr[minidx].done = 1;
//         }
//         else{
//             arr[i].ct = curr + arr[i].bt;
//             curr = arr[i].ct;
//             arr[i].done = 1;
//             i++;
//         }
//     }
//     for(int i=0;i<n;i++){
//         arr[i].tat = arr[i].ct - arr[i].at;     // calculate tat
//         arr[i].wt = arr[i].tat - arr[i].bt;     // calculate wt
//     }
    
// }

void Calculate(int n) {
    int completed = 0, curr = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        // Check the ready queue -> choose the process with the shortest burst time
        for (int i = 0; i < n; i++) {
            if (!arr[i].done && arr[i].at <= curr) {
                if (arr[i].bt < min_bt || 
                   (arr[i].bt == min_bt && arr[i].at < arr[idx].at) || 
                   (arr[i].bt == min_bt && arr[i].at == arr[idx].at && arr[i].pid < arr[idx].pid)) {
                    min_bt = arr[i].bt;
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
    float sumCT  = 0;
    for(int i=0;i<n;i++){
        sumTAT += arr[i].tat;
        sumCT += arr[i].wt;
    }
    printf("total TAT = %.2f & avg TAT = %.2f\n",sumTAT,sumTAT/n);
    printf("total CT = %.2f & avg CT = %.2f",sumCT,sumCT/n);


    return 0;
}