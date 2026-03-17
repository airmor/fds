#include <stdio.h>
#include <stdlib.h>

void quick_sort(int arr[], int left, int right) {
    if (left >= right) return;
    int i = left, j = right, pivot = arr[left];
    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        if (i < j) arr[i++] = arr[j];
        while (i < j && arr[i] <= pivot) i++;
        if (i < j) arr[j--] = arr[i];
    }
    arr[i] = pivot;
    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
}

void my_sort(int arr[], int n) {
    quick_sort(arr, 0, n - 1);
}


int main() {
    int N,M;
    scanf("%d %d",&N,&M);
    int* arr = (int*)malloc(M*sizeof(int));
    for(int i=0;i<M;i++){
        scanf("%d",&arr[i]);
    }
    my_sort(arr,M);
    int local=arr[0];
    printf("%d",local);
    for(int i=0;i<N-M;i++){
        int tmp;
        scanf("%d",&tmp);
        if(tmp>local){
            int j=0;
            while(arr[j]<local){
                j++;
            }
            if(j==M-1 || arr[j+1]>tmp){
                local=tmp;
                printf(" %d",local);
                arr[j]=tmp;
            }else{
                printf(" %d",arr[j+1]);
                local=arr[j+1];
                for(j;j<M-1;j++){
                    arr[j]=arr[j+1];
                    if(arr[j+1]>tmp){
                        arr[j]=tmp;
                        break;
                    }
                    if(j==M-2){
                        arr[j+1]=tmp;
                    }
                }
            }
        }else{
            int j=0;
            while(arr[j]<tmp){
                j++;
            }
            int temp=arr[j];
            arr[j]=tmp;
            tmp=temp;
            while(tmp!=local){
                int temp=arr[j];
                arr[j]=tmp;
                tmp=temp;
                j++;
            }
            if(j==M-1){
                printf("\n");
                local=arr[0];
                printf("%d",local);
            }else{
                local=arr[j+1];
                printf(" %d",local);
            }
        }
    }
    
        int j=0;
        while(arr[j]!=local){   
            j++;
        }
        for(int k=j+1;k<M;k++){
            printf(" %d",arr[k]);
        }
        if(j==0){
            return 0;
        }else{
            printf("\n");
            printf("%d",arr[0]);
            for(int k=1;k<j;k++){
                printf(" %d",arr[k]);
            }
        }
    free(arr);
    return 0;
}