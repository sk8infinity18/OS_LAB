#include<stdio.h> 
#include<stdlib.h>
#include<math.h>
#include<limits.h>

void sort(int arr[], int n){
    for (int i = 0; i < n; i++){
        for (int j = 1; j < n-i; j++){
            if (arr[j-1]> arr[j]){
                int temp= arr[j-1];
                arr[j-1]= arr[j];
                arr[j]= temp;
            }
        }
    }
    
}
void FCFS(int req[], int n, int head){
    int seq[n];

    // Copy the sequence
    for (int i = 0; i < n; i++){
        seq[i]= req[i];
    }

    // Calculate Seek Time
    int time = abs(head- req[0]);

    for (int i = 1; i < n; i++){
        time+= abs(req[i]- req[i-1]);
    }
    

    // Print sequence
    printf("%d ", head);
    for (int i = 0; i < n; i++){
        printf("%d ", seq[i]);
    }
    
    printf("\nSeek time FCFS: %d", time);
}

void SSTF(int req[], int n, int head){
    int vis[n], seq[n], curr=head;
    int count=0;

    int time=0;
    // Initialise visited 
    for (int i = 0; i < n; i++){
        vis[i]=0;
    }

    while (count<n){
        int min= INT_MAX;
        int idx=-1;

        for (int i = 0; i < n; i++){
            if (!vis[i] && abs(req[i]- curr) < min){
                min= abs(req[i]- curr);
                idx=i;
            }
        }
        
        vis[idx]= 1;

        time+= abs(req[idx]- curr);
        curr = req[idx];
        seq[count++]= curr;
    }
    
    
    // Print sequence
    printf("\nSSTF seq: %d ", head);
    for (int i = 0; i < n; i++){
        printf("%d ", seq[i]);
    }
    
    printf("\nSeek time SSTF: %d", time);
}

void SCAN(int req[], int n, int head, int disk){
    int seq[n+2], arr[n+2];

    for (int i = 0; i < n; i++){
        arr[i]= req[i];
    }
    
    arr[n]=0;
    arr[n+1]= disk-1;

    sort(arr, n+2);

    // Get the breakpoint
    int pos=0;
    for (int i = 0; i < n+2; i++){
        if (head< arr[i]){
            pos=i;
            break;
        }
    }
    
    int count=0;

    int dir;
    printf("\nEnter the direction: ");
    scanf("%d", &dir);

    if (dir==1){
        for (int i = pos; i < n+2; i++){
        seq[count++]= arr[i];
        }
    
        for (int i = pos-1; i >=0; i--){
        seq[count++]= arr[i];
        }
    }else{
        for (int i = pos-1; i >=0; i--){
        seq[count++]= arr[i];
        }

        for (int i = pos; i < n+2; i++){
        seq[count++]= arr[i];
        }
    }
    // Print it

    printf("\nSCAN sequence: %d ", head);
    for (int i = 0; i < count-1; i++){
        printf("%d ", seq[i]);
    }
    
    int time= abs(head- seq[0]);

    for (int i = 1; i < count-1; i++){
        time+= abs(seq[i]- seq[i-1]);
    }
    
    printf("\nSCAN seek time: %d", time);
}

void CSCAN(int req[], int n, int head, int disk){

    int arr[n+2], seq[n+2];

    for (int i = 0; i < n; i++){
        arr[i]= req[i];
    }

    arr[n]=0;
    arr[n+1]=disk-1;

    sort(arr, n+2);

    int pos;
    
    for (int i = 0; i < n+2; i++){
        if (head< arr[i]){
            pos=i;
            break;
        }
        
    }

    int count=0;
    int dir;
    printf("\nEnter the direction: ");
    scanf("%d", &dir);

    if (dir==1){
        for (int i = pos; i < n+2; i++) seq[count++] = arr[i];
        for (int i = 0; i < pos; i++) seq[count++] = arr[i];
    }else{
        for (int i = pos-1; i >= 0; i--) seq[count++] = arr[i];
        for (int i = n+1; i >= pos; i--) seq[count++] = arr[i];
    }
    

    printf("CSCAN sequence: %d ", head);
    for (int i = 0; i < count; i++){
        printf("%d ", seq[i]);
    }
    
    // Get the seek time
    int time= abs(head- seq[0]);

    for (int i = 1; i < count; i++){
        time+= abs(seq[i]- seq[i-1]);
    }
    
    printf("\nCSCAN Seek time: %d", time);
}

void LOOK(int req[], int n, int head){
    int arr[n], seq[n];

    for (int i = 0; i < n; i++){
        arr[i]= req[i];
    }

    sort(arr,n);

    int pos;
    for (int i = 0; i < n; i++){
        if (head< arr[i]){
            pos= i;
            break;
        }
    }

    int dir;
    printf("Enter the direction: ");
    scanf("%d", &dir);

    int count=0;
    if (dir==1){
        for (int i = pos; i < n; i++) seq[count++]= arr[i];
        for (int i = pos-1; i >=0; i--) seq[count++]= arr[i];
    }else{
        
        for (int i = pos-1; i >=0; i--) seq[count++]= arr[i];
        for (int i = pos; i < n; i++) seq[count++]= arr[i];
    }
    
    printf("LOOK sequence: %d ", head);
    for (int i = 0; i < n; i++){
        printf("%d ", seq[i]);
    }

    int time= abs(head- seq[0]);

    for (int i = 1; i < n; i++){
        time+= abs(seq[i]- seq[i-1]);
    }
    
    printf("\nLOOK Seek Time: %d", time);
}

void CLOOK(int req[], int n, int head){
    int arr[n], seq[n];
    for (int i = 0; i < n; i++){
        arr[i]= req[i];
    }
    
    sort(arr,n);

    int pos;
    for(int i = 0; i < n; i++){
        if(head< arr[i]){
            pos=i;
            break;
        }
    }
    int dir;
    printf("Enter the direction: ");
    scanf("%d", &dir);

    int count=0;
    
    if (dir==1){
        for (int i = pos; i < n; i++) seq[count++]= arr[i];
        for (int i = 0; i < pos; i++) seq[count++]= arr[i];
    }else{
        for (int i = pos-1; i >= 0; i--) seq[count++]= arr[i];
        for (int i = n-1; i >= pos; i--) seq[count++]= arr[i];
    }
    
    printf("CLOOK Sequence: %d ", head);
    for (int i = 0; i < count; i++)
        printf("%d ", seq[i]);
    
    int time= abs(head - seq[0]);
    for (int i = 1; i < count; i++) 
        time+= abs(seq[i]- seq[i-1]);
    printf("\nCLOOK Seek time: %d", time);

}
int main(){
    int n, head;

    printf("Enter the no of requests and head position: ");
    scanf("%d %d", &n, &head);

    int req[n];

    printf("Enter the requests sequence: ");

    for (int i = 0; i < n; i++){
        scanf("%d", &req[i]);
    }
    
    int size;
    printf("Enter the no of tracks: ");
    scanf("%d", &size);

    // FCFS(req,n,head);
    // SSTF(req,n, head);
    // SCAN(req,n,head,size);
    // CSCAN(req,n,head,size);
    // LOOK(req,n,head);
    CLOOK(req,n,head);
    return 0;
}

// 82 170 43 140 24 16 190