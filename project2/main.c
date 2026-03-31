#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define MAX_n 200000
#define MAX_k 2000000000

typedef struct Node* Tree;
typedef struct Node Node;
typedef int bool; 



struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

Tree read_inport(Node** node);//read the inport information of the Binary Search Tree,and return the Binary Search Tree

Tree build_tree(int* parent_node_index,Node* node,int n);//build the Binary Search Tree with the inport information, and return the Binary Search Tree

bool find_sum_is_N(Tree T1,Tree T2,int N,bool flag,int* A);//find the number A from T1 and B from T2 such that A+B=N,if such A and B exist, return true, otherwise return false

bool find_n_in_tree(Tree root,int n);//find the number of nodes in the Binary Search Tree T with value n,if such nodes exist, return true, otherwise return false

bool print_preorder_traversal(Tree root);//print the preorder traversal of the Binary Search Tree T, and return true if the Binary Search Tree is not empty, otherwise return false

bool print_result(Tree tree);//Print the tree with the preorder traversal.The values in each line are separated by 1 space, and there must be no extra space at the beginning or the end of the line.

int main()
{
    Node* T1_node=NULL;
    Node* T2_node=NULL;
    Tree T1=read_inport(&T1_node);
    if(T1==NULL)
    {
        printf("The Binary Search Tree is empty!");
        return 0;
    }
    Tree T2=read_inport(&T2_node);
    if(T2==NULL)
    {
        printf("The Binary Search Tree is empty!");
        return 0;
    }
    int N;
    scanf("%d",&N);
    if(N<-MAX_k||N>MAX_k)
    {
        printf("Invalid input for the target value N!");
        return 0;
    }
    int A=-MAX_k-1;
    if(!find_sum_is_N(T1,T2,N,false,&A)){
        printf("false\n");
    }
    print_result(T1);
    print_result(T2);
    free(T1_node);
    free(T2_node);
    return 0;
}

Tree read_inport(Node** node)//read the inport information of the Binary Search Tree,and return the Binary Search Tree
{
    int n;
    scanf("%d", &n);
    if(n<=0||n>MAX_n)
    {
        printf("Invalid input for the number of nodes in the Binary Search Tree!");
        return NULL;
    }
    *node=(Node*)malloc(sizeof(Node)*n);
    if(*node==NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    int* parent_node_index=(int*)malloc(sizeof(int)*n);
    if(parent_node_index==NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    memset(parent_node_index,0,sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&(*node)[i].data,&parent_node_index[i]);
        (*node)[i].left=NULL;
        (*node)[i].right=NULL;
        if(parent_node_index[i]<-1||parent_node_index[i]>=n)
        {
            printf("Invalid input for the parent node index!");
            free(*node);
            free(parent_node_index);
            return NULL;
        }
        if((*node)[i].data<-MAX_k||(*node)[i].data>MAX_k)
        {
            printf("Invalid input for the node value!");
            free(*node);
            free(parent_node_index);
            return NULL;
        }
    }
    Tree tree=build_tree(parent_node_index,*node,n);
    free(parent_node_index);
    return tree;
}

Tree build_tree(int* parent_node_index,Node* node,int n)//build the Binary Search Tree with the inport information, and return the Binary Search Tree
{
    Tree tree=NULL;
    for(int i=0;i<n;i++)
    {
        if(parent_node_index[i]==-1)
        {
            tree=&node[i];
        }
        else
        {
            if(node[i].data<node[parent_node_index[i]].data)
            {
                node[parent_node_index[i]].left=&node[i];
            }
            else
            {
                node[parent_node_index[i]].right=&node[i];
            }
        }
    }
    return tree;
}

bool find_sum_is_N(Tree T1,Tree T2,int N,bool flag,int* A)//find the number A from T1 and B from T2 such that A+B=N,if such A and B exist, return true, otherwise return false
{
    if(T1==NULL||T2==NULL)
    {
        return false;
    }
    flag=find_sum_is_N(T1->left,T2,N,flag,A)||flag;
    if(*A!=T1->data && find_n_in_tree(T2,N-T1->data))
    {
        if(!flag)
        {
            printf("true\n");
            flag=true;
        }
        printf("%d = %d + %d\n",N,T1->data,N-T1->data);
        *A=T1->data;
    }
    flag=find_sum_is_N(T1->right,T2,N,flag,A)||flag;
    return flag;
}

bool find_n_in_tree(Node* root,int n)//find the number of nodes in the Binary Search Tree T with value n,if such nodes exist, return true, otherwise return false
{
    if(root==NULL)
    {
        return false;
    }
    if(root->data==n)
    {
        return true;
    }
    else if(root->data>n)
    {
        return find_n_in_tree(root->left,n);
    }
    else
    {
        return find_n_in_tree(root->right,n);
    }
}

bool print_preorder_traversal(Tree root)//print the preorder traversal of the Binary Search Tree T, and return true if the Binary Search Tree is not empty, otherwise return false
{
    if(root==NULL)
    {
        return false;
    }
    printf(" %d",root->data);
    print_preorder_traversal(root->left);
    print_preorder_traversal(root->right);
    return true;
}

bool print_result(Tree tree)//Print the tree with the preorder traversal.The values in each line are separated by 1 space, and there must be no extra space at the beginning or the end of the line.
{
    if(tree==NULL)
    {
        return false;
    }
    printf("%d",tree->data);
    print_preorder_traversal(tree->left);
    print_preorder_traversal(tree->right);
    printf("\n");
    return true;
}