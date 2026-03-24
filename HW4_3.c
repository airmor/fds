#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

void print_postorder(struct Node* root, int d0){
    if(root==NULL) return;
    print_postorder(root->left, d0);
    print_postorder(root->right, d0);
    if(root->data==d0){
        printf("%d\n", root->data);
        return;
    }
    printf("%d ", root->data);
}


int main(){
    int n;
    scanf("%d", &n);
    int stack[30]={0};
    int top=-1;
    struct Node* arr = (struct Node*)malloc(n*sizeof(struct Node));
    int sw = 0;//0->上一个是push 1->上一个是pop
    int num=0;
    while(num<n){
        char c[100];
        scanf("%s", &c);
        if(c[1]=='o'){
            sw=1;
            top--;
        }
        else{
            scanf("%d", &arr[num].data);
            if(num==0){
                arr[num].left=NULL;
                arr[num].right=NULL;
            }
            else if(sw==0){
                arr[num-1].left=&arr[num];
                arr[num].right=NULL;
                arr[num].left=NULL;
            }
            else{
                arr[stack[top+1]].right=&arr[num];
                arr[num].left=NULL;
                arr[num].right=NULL;
            }
            top++;
            stack[top]=num;
            num++;
            sw=0;
        }
    }
    print_postorder(&arr[0], arr[0].data);
    return 0;
}