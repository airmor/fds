#include <stdio.h>

int main() {
    int a[201][201]= {0};
    int N,M;
    scanf("%d %d",&N,&M);
    for(int i=0; i<M; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        a[x][y]=1;
        a[y][x]=1;
    }
    int K;
    scanf("%d",&K);
    for(int i=0; i<K; i++){
        int n;
        int data[201]= {0};
        scanf("%d",&n);
        int now,next,condition=1;
        scanf("%d",&now);
        int first=now;
        for(int j=1; j<n; j++){
            scanf("%d",&next);
            if(a[now][next]==0){
                condition=0;
            }
            now=next;
            if(data[now]>0){
                condition=0;
            }
            data[now]++;
        }
        for(int j=1; j<=N; j++){
            if(data[j]==0){
                condition=0;
            }
        }
        if(now!=first){
            condition=0;
        }
        if(condition==1){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}