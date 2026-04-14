#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    int parent;
};

int MAX(int a, int b){
    return a > b ? a : b;
}

int find(struct node *nodes, int x){
    if(nodes[x].parent == 0) return x;
    else return find(nodes, nodes[x].parent);
}

int change(struct node *nodes, int x, int root){
    while(x!=0){
        int temp = nodes[x].parent;
        nodes[x].parent = root;
        x = temp;
    }
    return 0;
}

int main(){
    int n;
    scanf("%d\n", &n);
    struct node *nodes = (struct node *)malloc((n+1) * sizeof(struct node));
    memset(nodes, 0, (n+1) * sizeof(struct node));
    nodes[0].data = n;
    int menber=0;
    while(1){
        char c = getchar();
        if(c == 'S') break;
        else if (c == 'I'){
            int a, b;
            scanf("%d %d\n", &a, &b);
            if(find(nodes, a) == 0 && find(nodes, b) == 0){
                if(a < b) {nodes[a].parent = b;}
                else nodes[b].parent = a;
                nodes[0].data--;
            }
            else if(find(nodes, a) == 0){
                nodes[a].parent = find(nodes, b);
                nodes[0].data--;
            }
            else if(find(nodes, b) == 0){
                nodes[b].parent = find(nodes, a);
                nodes[0].data--;
            }
            else{
                int rootA = find(nodes, a);
                int rootB = find(nodes, b);
                if(rootA != rootB){
if(b<menber){                    if(rootA < rootB) {nodes[rootA].parent=rootB;}
                    else nodes[rootB].parent=rootA;}
                    else{
                        if(rootA < rootB) {nodes[rootB].parent=rootA;}
                    else nodes[rootA].parent=rootB;
                }
                    nodes[0].data--;
                }
            }
            menber=b;
        }
        else if (c == 'C'){
            int a, b;
            scanf("%d %d\n", &a, &b);
            if(find(nodes, a) == find(nodes, b)){
                printf("yes\n");
            }
            else{
                printf("no\n");
            }
        }
    }
    if(nodes[0].data == 1){
        printf("The network is connected.\n");
    }
    else{
        printf("There are %d components.\n", nodes[0].data);
    }
    free(nodes);
    return 0;
}