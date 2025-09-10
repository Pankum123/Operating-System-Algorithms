#include<stdio.h>
#include<limits.h>

#define MAX 20

int queue[MAX];
int front = -1, rear = -1;

int isEmpty() {
    return (front == -1 || front > rear);
}

// Function to check if queue is full
int isFull() {
    return rear == MAX - 1;
}


// Function to insert element into queue
void push(int value) {
    if (rear == MAX - 1) {
        return;
    } else {
        if (front == -1)  // First element insertion
            front = 0;
        rear++;
        queue[rear] = value;
    }
}

// Function to delete element from queue
void pop() {
    if (front == -1 || front > rear) {
       return;
    } else {
        front++;
    }
}


struct RoundRobin{
    int pid,at,bt,ct,tat,wt;
    int done;
};

struct RoundRobin arr[MAX];

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
    push(0);
    int i = 1;
    while(!isEmpty()){
        int idx = queue[front];
        pop();
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
            push(i);
            i++;
        }
        if(copybt[idx] > 0) push(idx);
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