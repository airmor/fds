#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1 // Define true as 1
#define false 0 // Define false as 0
#define MAX_n 200000 // Maximum number of nodes
#define MAX_k 2000000000 // Maximum value of node key

typedef struct Node* Tree; // Define Tree as pointer to Node
typedef struct Node Node; // Define Node as struct Node
typedef int bool; // Define bool as int

struct Node{ // Node structure for Binary Search Tree
    int data;    // Key value
    struct Node* left;    // Left child pointer
    struct Node* right;    // Right child pointer
};

Tree read_inport(Node** node,int* num);//read the inport information of the Binary Search Tree,and return the Binary Search Tree

Tree build_tree(int* parent_node_index,Node* node,int n);//build the Binary Search Tree with the inport information, and return the Binary Search Tree

bool find_sum_is_N(Tree T1,Tree T2,int N,bool flag,int* A);//find the number A from T1 and B from T2 such that A+B=N,if such A and B exist, return true, otherwise return false

bool find_n_in_tree(Tree root,int n);//find the number of nodes in the Binary Search Tree T with value n,if such nodes exist, return true, otherwise return false

bool print_preorder_traversal(Tree root);//print the preorder traversal of the Binary Search Tree T, and return true if the Binary Search Tree is not empty, otherwise return false

bool print_result(Tree tree);//Print the tree with the preorder traversal.The values in each line are separated by 1 space, and there must be no extra space at the beginning or the end of the line.

bool check(int n,Tree tree,int*now,int*count);//check if the number of nodes in the Binary Search Tree T is n and the tree is a valid BST, if true, return true, otherwise return false

int main()// Main function: entry point of the program
{
    Node* T1_node=NULL;    // Pointer to array of nodes for T1
    Node* T2_node=NULL;    // Pointer to array of nodes for T2
    int n1=0,n2=0;    // Number of nodes in T1 and T2
    Tree T1=read_inport(&T1_node,&n1);    // Read T1 BST from input
    if(T1==NULL)     // Check if T1 is empty
    {
        printf("The Binary Search Tree is empty!\n");
        return 0;
    }
    Tree T2=read_inport(&T2_node,&n2);    // Read T2 BST from input
    if(T2==NULL)    // Check if T2 is empty
    {
        printf("The Binary Search Tree is empty!\n");
        return 0;
    }
    int now=-MAX_k-1;    // Initialize now with a value outside valid range (to avoid matching first node)
    int count=0;    // Initialize count for node counting in check function
    if(!(check(n1,T1,&now,&count)&&count==n1))    // Check if T1 is a valid BST with n1 nodes
    {
        printf("Invalid input for the Binary Search Tree!\n");
        return 0;
    }
    now=-MAX_k-1;    // Reset now for T2
    count=0;    // Reset count for node counting in check function
    if(!(check(n2,T2,&now,&count)&&count==n2))    // Check if T2 is a valid BST with n2 nodes
    {
        printf("Invalid input for the Binary Search Tree!\n");
        return 0;
    }
    // Get target sum N
    int N;
    scanf("%d",&N);

    if(N<-MAX_k||N>MAX_k)    // Validate N range
    {
        // Print error message
        printf("Invalid input for the target value N!\n");
        // Exit program
        return 0;
    }

    int A=-MAX_k-1;    // Initialize A with a value outside valid range (to avoid matching first node)

    if(!find_sum_is_N(T1,T2,N,false,&A))    // Find if there exists A in T1 and B in T2 such that A+B=N
    {
        // If no solution found, print false
        printf("false\n");
    }

    print_result(T1);    // Print preorder traversal of T1
    print_result(T2);    // Print preorder traversal of T2

    // Free memory
    free(T1_node);
    free(T2_node);

    return 0;
}

//Node** node - pointer to array of nodes for the BST
Tree read_inport(Node** node,int* num)//read the inport information of the Binary Search Tree,and return the Binary Search Tree
{
    // Get number of nodes
    int n;
    scanf("%d", &n);
    *num=n;    // Store number of nodes in provided pointer
    if(n<=0||n>MAX_n)    // Validate n range
    {
        printf("Invalid input for the number of nodes in the Binary Search Tree!\n");
        return NULL;        // Return NULL indicating error
    }

    *node=(Node*)malloc(sizeof(Node)*n);    // Allocate memory for array of n nodes

    if(*node==NULL)    // Check if allocation succeeded
    {
        printf("Memory allocation failed!\n");
        return NULL;        // Return NULL indicating error
    }

    int* parent_node_index=(int*)malloc(sizeof(int)*n);    // Allocate memory for parent node index array

    if(parent_node_index==NULL)    // Check if allocation succeeded
    {
        printf("Memory allocation failed!\n");
        return NULL;        // Return NULL indicating error
    }

    memset(parent_node_index,0,sizeof(int)*n);    // Initialize parent_node_index array to zeros

    for(int i=0;i<n;i++)//Get node data and parent index for each node
    {

        scanf("%d %d",&(*node)[i].data,&parent_node_index[i]);        // Read node data and parent index
        (*node)[i].left=NULL;        // Initialize left child pointer to NULL
        (*node)[i].right=NULL;        // Initialize right child pointer to NULL

        if(parent_node_index[i]<-1 || parent_node_index[i]>=n)        // Validate parent index range
        {
            printf("Invalid input for the parent node index!\n");
            // Free allocated memory
            free(*node);
            free(parent_node_index);
            return NULL;        // Return NULL indicating error
        }

        if((*node)[i].data<-MAX_k || (*node)[i].data>MAX_k)        // Validate node data range
        {
            printf("Invalid input for the node value!\n");
            // Free allocated memory
            free(*node);
            free(parent_node_index);
            return NULL;        // Return NULL indicating error
        }
    }

    Tree tree=build_tree(parent_node_index,*node,n);    // Build BST from parent indices
    free(parent_node_index);    // Free parent index array

    return tree;
}

/*parent_node_index - array of parent node indices for each node
  node - array of nodes with data and child pointers initialized to NULL
  n - number of nodes in the BST
*/
Tree build_tree(int* parent_node_index,Node* node,int n)//build the Binary Search Tree with the inport information, and return the Binary Search Tree
{
    Tree tree=NULL;    // Initialize tree root as NULL

    for(int i=0;i<n;i++)    // build BST through each node
    {
        if(parent_node_index[i]==-1)        // If parent index is -1, this node is the root
        {
            tree=&node[i];        // Set tree root to current node
        }
        else
        {
            if(node[i].data<node[parent_node_index[i]].data)        // If current node's data is less than parent's data
            {
                node[parent_node_index[i]].left=&node[i];        // Attach current node as left child of parent
            }
            else        // If current node's data is greater than or equal to parent's data
            {
                node[parent_node_index[i]].right=&node[i];        // Attach current node as right child of parent
            }
        }
    }
    return tree;
}

/*Tree T1 - first BST;
  T2 - second BST;
  N - target sum;
  flag - flag indicating if solution found,if true, solution found now, if false, solution not found now;
  A - pointer to variable to store solution which means the current max A for A+B=N*/
bool find_sum_is_N(Tree T1,Tree T2,int N,bool flag,int* A)//find the number A from T1 and B from T2 such that A+B=N,if such A and B exist, return true, otherwise return false
{
    if(T1==NULL||T2==NULL)    // If either tree is empty, return false
    {
        return false;
    }

    flag=find_sum_is_N(T1->left,T2,N,flag,A)||flag;    // Recursively search left subtree of T1

    if(*A!=T1->data && find_n_in_tree(T2,N-T1->data))    // If current node's value not already used as A and (N - T1->data) exists in T2
    {
        if(!flag)        // If this is the first solution found
        {
            printf("true\n");
            flag=true;
        }
        printf("%d = %d + %d\n",N,T1->data,N-T1->data);        // Print the equation N = A + B
        *A=T1->data;        // Store current node's value in A to avoid duplicate printing
    }

    flag=find_sum_is_N(T1->right,T2,N,flag,A)||flag;    // Recursively search right subtree of T1

    return flag;
}

/*root - root of BST to search;
  n - value to find in the BST
*/
bool find_n_in_tree(Node* root,int n)//find the number of nodes in the Binary Search Tree T with value n,if such nodes exist, return true, otherwise return false
{
    if(root==NULL)    // If root is NULL, value not found
    {
        return false;
    }
    if(root->data==n)    // If current node's data equals n, found
    {
        return true;
    }
    else if(root->data>n)    // If current node's data greater than n, search left subtree
    {
        return find_n_in_tree(root->left,n);
    }
    else    // Else search right subtree
    {
        return find_n_in_tree(root->right,n);
    }
}

// root - root of BST to print
bool print_preorder_traversal(Tree root)//print the preorder traversal of the Binary Search Tree T, and return true if the Binary Search Tree is not empty, otherwise return false
{
    if(root==NULL)    // If root is NULL, return false
    {
        return false;
    }
    printf(" %d",root->data);    // Print node data with leading space
    print_preorder_traversal(root->left);    // Recursively print left subtree
    print_preorder_traversal(root->right);    // Recursively print right subtree
    return true;
}

// tree - root of BST to print
bool print_result(Tree tree)//Print the tree with the preorder traversal.The values in each line are separated by 1 space, and there must be no extra space at the beginning or the end of the line.
{
    if(tree==NULL)    // If tree is NULL, return false
    {
        return false;
    }
    
    printf("%d",tree->data);    // Print root data without leading space
    print_preorder_traversal(tree->left);    // Print left subtree with leading spaces handled by print_preorder_traversal
    print_preorder_traversal(tree->right);    // Print right subtree with leading spaces handled by print_preorder_traversal
    printf("\n");    // Print newline

    return true;
}

/*n - expected number of nodes in the BST;
  tree - root of BST to check;
  now - pointer to variable to count nodes during traversal
*/
bool check(int n,Tree tree,int*now,int*count)//check if the number of nodes in the Binary Search Tree T is n and the tree is a valid BST, if true, return true, otherwise return false
{
    if(tree==NULL)    // If tree is NULL, return true (empty tree is a valid BST)
    {
        return true;
    }
    bool left_check=check(n,tree->left,now,count);    // Recursively check left subtree
    if(tree->data<*now)    // If current node's data is less than previous node's data, it's not a valid BST
    {
        return false;
    }
    *now=tree->data;    // Update now to current node's data
    (*count)++;    // Increment node count
    bool right_check=check(n,tree->right,now,count);    // Recursively check right subtree
    return left_check && right_check;    // Return true if both left and right subtrees are valid BSTs
}