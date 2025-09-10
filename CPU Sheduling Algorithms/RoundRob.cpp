#include<iostream>
#include<climits>
#include<queue>
using namespace std;

#define MAX 20

struct RoundRobin{
    int pid,at,bt,ct,tat,wt;
    int done;
};

struct RoundRobin arr[MAX];
queue<int>ready;

void Calculate(int n,int tq) {
    
    // sorting -> Arrival time
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j].at > arr[j+1].at || (arr[j].at == arr[j + 1].at && arr[j].pid > arr[j + 1].pid) ){
                struct RoundRobin temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    int copybt[n];
    for(int i=0;i<n;i++){
        copybt[i] = arr[i].bt;
    }

    int curr = 0;
    ready.push(0);
    int i = 1;
    while(!ready.empty()){
        int idx = ready.front();
        ready.pop();
        if(arr[idx].at > curr) curr = arr[idx].at;
        if(copybt[idx] <= tq){
            arr[idx].ct = curr + copybt[idx];
            copybt[idx] = 0;
        } 
        else {
            arr[idx].ct = curr + tq;
            copybt[idx] -= tq; 
        }
        curr = arr[idx].ct;
    
        while(i < n && arr[i].at <= curr){
            ready.push(i);
            i++;
        }
        if(copybt[idx] > 0) ready.push(idx);
    }

    for(int i=0;i<n;i++){
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
        arr[i].done = 0;
    }

    Calculate(n,2);

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