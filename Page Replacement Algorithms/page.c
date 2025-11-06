#include<stdio.h> 
#include<stdlib.h>

void fifo(int pages[], int fc, int n){

    int *frames= (int*)malloc(fc*sizeof(int));

    int index=0, faults=0;
    for (int i = 0; i < fc; i++){
        frames[i]=-1;
    }
    
    int found;
    for (int i = 0; i < n; i++){
        found=0;

        for (int j = 0; j < fc; j++){
            if (frames[j]==pages[i]){
                found=1;
                break;
            }
        }
        
        if (!found){
            frames[index]= pages[i];
            index= (index+1)  % fc;
            faults++;
        }

        printf("After page %d -> ", pages[i]);
        for (int i = 0; i < fc; i++){
            if (frames[i]==-1)
                printf(" - ");
            else printf("%2d", frames[i]);    
        }
        printf(found? " (Hit)\n" : " (Fault)\n");
    }
}

int findlru(int time[], int fc ){
    int min= time[0];
    int pos=0;

    for (int i = 1; i < fc; i++){
        if (time[i]< min){
            min=time[i];
            pos=i;
        }
    }

    return pos;
    
}
void lru(int pages[], int fc, int n){
    int* frames= (int*)malloc(fc * sizeof(int));
    int* time= (int*)malloc(fc * sizeof(int));

    int faults=0;
    for (int i = 0; i < fc; i++){
        frames[i]=-1;
    }
    
    int found, count=0;
    for (int i = 0; i < n; i++){
        found=0;
        for (int j = 0; j < fc; j++){
            if (frames[j]== pages[i])
            {
                found=1;
                time[j]= ++count;
                break;            
            }
        }

        if (!found){
            int pos=-1;
            for (int i = 0; i < fc; i++){
                if (frames[i]==-1){
                    pos=i;
                    break;
                }
            }
            
            if (pos==-1) pos= findlru(time, fc);
            frames[pos]= pages[i];
            time[pos]=++count;
            faults++;
        }

    printf("After page %d -> ", pages[i]);
        for (int i = 0; i < fc; i++){
            if(frames[i]==-1) printf(" - ");
            else printf("%2d", frames[i]);
        }
        printf(found? " (Hit)\n" : " (Fault)\n");
    }

    printf("Page faults: %d\n", faults);
    printf("Hits: %d\n", n-faults);
}

int predict(int frames[], int pages[], int n, int index, int fc){
    int result=-1;
    int far=index;
    for (int i = 0; i < fc; i++){
        int j;
        for (j = index; j < n; j++){
            if (frames[i]== pages[j]){
                if (j>far){
                    far=j;
                    result=i;
                }
                break;
            }
        }
        if (j==n) return i;
    }

    int ans= (result==-1) ? 0 : result;
    return ans;
    
}
void optimal(int pages[], int fc, int n){
    int frames[fc];

    for (int i = 0; i < fc; i++){
        frames[i]=-1;
    }

    int found, faults=0;
    for (int i = 0; i < n; i++){
        found=0;
        for (int j = 0; j < fc; j++){
            if (frames[j]==pages[i]){
                found=1;
                break;
            }
        }

        if (!found){
            int empty=-1;
            for (int j = 0; j < fc; j++){
                if (frames[j]==-1){
                    empty=j;
                    break;
                }
            }
            
            if (empty!=-1) frames[empty]= pages[i];
            else frames[predict(frames, pages, n, i+1, fc)]= pages[i];
            faults++;
        }
        
        printf("After page %d -> ", pages[i]);
        for (int i = 0; i < fc; i++){
            if(frames[i]==-1) printf(" - ");
            else printf("%2d", frames[i]);
        }
        printf(found? " (Hit)\n" : " (Fault)\n");
    }

    printf("Page faults: %d\n", faults);
    printf("Hits: %d\n", n-faults);
    
}
int main(){
    int n, fc;

    printf("Enter the no of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter the no of frames: ");
    scanf("%d", &fc);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++){
        scanf("%d", &pages[i]);
    }
    
    // fifo(pages,fc,n);
    // optimal(pages,fc,n);
    lru(pages,fc,n);
    return 0;
}
