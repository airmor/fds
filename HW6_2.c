#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};



struct Node* build(int* arr, int n){
    if(n==0) return NULL;
    struct Node* root= (struct Node*)malloc(sizeof(struct Node));
    root->data=arr[n/2];
    root->left=build(arr, n/2);
    root->right=build(arr+n/2+1, n/2);
    return root;
}

void print(struct Node* root, int level, int i){
    if(root == NULL) return;
    if(level == i) printf(" %d", root->data);
    else{
        print(root->left, level+1, i);
        print(root->right, level+1, i);
    }
    return;
}

int main(){
    int n;
    scanf("%d", &n);
    int* arr= (int*)malloc(n * sizeof(int));
    int* hool= (int*)malloc(3000 * sizeof(int));
    int tmp;
    for(int i=0; i<n; i++){
        scanf("%d", &tmp);
        hool[tmp]++;
    }
    int j=0;
    for(int i=0; i<2001; i++){
        if(hool[i]>0){
            arr[j]=i;
            j++;
        }
    }
    int deep=0;
    int sheng=0;
    if(0<n&&n<2) {printf("%d\n", arr[0]); return 0;}
    else if(n<4) {deep=1;sheng=n-2+1;}
    else if(n<8) {deep=2;sheng=n-4+1;}
    else if(n<16) {deep=3;sheng=n-8+1;}
    else if(n<32) {deep=4;sheng=n-16+1;}
    else if(n<64) {deep=5;sheng=n-32+1;}
    else if(n<128) {deep=6;sheng=n-64+1;}
    else if(n<256) {deep=7;sheng=n-128+1;}
    else if(n<512) {deep=8;sheng=n-256+1;}
    else if(n<1024) {deep=9;sheng=n-512+1;}
    else if(n<2048) {deep=10;sheng=n-1024+1;}
    int* arr2= (int*)malloc((n-sheng )* sizeof(int));
    j=0;
    for(int i=0; i<n; i++){
        if(i%2!=0 || i/2>=sheng){
            arr2[j]=arr[i];
            j++;
        }
    }
    struct Node* root=build(arr2, n-sheng);
    printf("%d", root->data);
    for(int i=2; i<=deep; i++){
        print(root, 1, i);
    }
    for(int i=0; i<sheng; i++){
        printf(" %d", arr[i*2]);
    }
    printf("\n");
    return 0;
}