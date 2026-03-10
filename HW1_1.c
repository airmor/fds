#include <stdio.h>
#include <stdlib.h>

int main() {
    int n=0,h=0;
    scanf("%d %d",&n,&h);
    int *arr = (int*) malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    int Position=0,NUM=0;
    for(int i=0;i<n;i++){
        int CN=1;
        while(i-CN>=0 && arr[i]-h<=arr[i-CN]){
            CN++;
        }
        if(CN>NUM){
            NUM=CN;
            Position=arr[i]-h;
        }
    }
    printf("%d %d\n",Position,NUM);
    return 0;
}