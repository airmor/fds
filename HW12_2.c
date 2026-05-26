#include <stdio.h>

int main(){
    int arr[100]={0};
    int tmp[100]={0};
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    for(int i=0; i<n; i++){
        scanf("%d", &tmp[i]);
    }
    int locate=1;
    while(locate<n && tmp[locate]>=tmp[locate-1]){
        locate++;
    }
    int sw=1;
    int tmp_locate=locate;
    while(sw && tmp_locate<n){
        if(tmp[tmp_locate]==arr[tmp_locate]){
            tmp_locate++;
        }
        else{
            sw=0;
        }
    }
    if(sw){
        printf("Insertion Sort\n");
        int temp=tmp[locate];
        int i=locate;
        for(i=locate; i>0; i--){
            if(tmp[i-1]>temp){
                tmp[i]=tmp[i-1];
            }
            else{
                break;
            }
        }
        tmp[i]=temp;
        printf("%d", tmp[0]);
        for(int i=1; i<n; i++){
            printf(" %d", tmp[i]);
        }
    }
    else{
        printf("Heap Sort\n");
        locate=n-1;
        while(locate>0 && tmp[locate]>=tmp[0]){
            locate--;
        }
        int temp=tmp[locate];
        tmp[locate]=tmp[0];
        tmp[0]=temp;
        int now=0;
        int child=(now+1)*2-1;
        if(tmp[child]<tmp[child+1] && child+1<locate){
            child++;
        }
        while(child<locate && tmp[now]<tmp[child]){
            int temp=tmp[now];
            tmp[now]=tmp[child];
            tmp[child]=temp;
            now=child;
            child=(now+1)*2-1;
            if(tmp[child]<tmp[child+1] && child+1<locate){
                child++;
            }
        }
        printf("%d", tmp[0]);
        for(int i=1; i<n; i++){
            printf(" %d", tmp[i]);
        }
    }

    return 0;
}