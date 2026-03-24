#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* buildTree(int in_order[], int post_order[], int n) {
    if(n == 0) return NULL;
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = post_order[n-1];
    int i = 0;
    while(in_order[i] != root->data) i++;
    root->left = buildTree(in_order, post_order, i);
    root->right = buildTree(in_order+i+1, post_order+i, n-i-1);
    return root;
}

void printz(struct Node* root, int level, int i){
    if(root == NULL) return;
    if(level == i) printf(" %d", root->data);
    else{
        if(i%2 == 0){
            printz(root->right, level+1, i);
            printz(root->left, level+1, i);
        }else{
            printz(root->left, level+1, i);
            printz(root->right, level+1, i);
        }
    }
}

void print(struct Node* root) {
    printf("%d", root->data);
    for(int i = 1; i < 30; i++){
        printz(root, 0, i);
    }printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    int in_order[30];
    int post_order[30];
    for(int i = 0; i < n; i++){
        scanf("%d", &in_order[i]);  
    }
    for(int i = 0; i < n; i++){
        scanf("%d", &post_order[i]);  
    }
    struct Node* root = buildTree(in_order, post_order, n);
    print(root);
    return 0;
}