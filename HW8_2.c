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
        scanf("%d",&n);
        int now,next,condition=1;
        scanf("%d",&now);
        for(int j=1; j<n; j++){
            scanf("%d",&next);
            if(a[now][next]==0){
                condition=0;
            }
            now=next;
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