#include <stdio.h>  
#include <stdlib.h>  

int main() {  
    int n=0;
    int arr[1000]={0};
    int front=0;
    int rear=0;
    int n_left=0;
    int n_right=0;
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        char c;
        before:
        scanf("%c", &c);
        if(c=='I'){
            int tmp;
            scanf("%d", &tmp);
            arr[rear]=tmp;
            rear++;
            n_left++;
        }else if(c=='O'){
            if(n_right==0){
                if(n_left==0){
                    printf("ERROR\n");
                }else{
                    printf("%d %d\n", arr[front], n_left*2+1);
                    front++;
                    n_right=n_left-1;
                    n_left=0;
                }
            }else{
                printf("%d 1\n", arr[front]);
                front++;
                n_right--;
            }
        }else{
            goto before;
        }
    }
    return 0;
}