---
title: "Document"
output:
  word_document:
    path: D:\ZJU\homework\fds\project_2\report.docx
---

# Title of Project

A+B with Binary Search Trees (Project 2)

# Author's Name

[Fill in your name]

# Date

[Fill in the date]

## Chapter 1: Introduction

### 1.1 Problem Description

A Binary Search Tree (BST) is recursively defined as a binary tree with these properties:

1. The left subtree of a node contains only nodes with keys less than the node's key.
2. The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
3. Both the left and right subtrees are also BSTs.

Given two BSTs `T1` and `T2`, and an integer `N`, this project needs to find all pairs `(A, B)` such that:

- `A` is a value in `T1`
- `B` is a value in `T2`
- `A + B = N`

If multiple solutions exist, equations must be printed in ascending order of `A`, and duplicate equations must not be repeated.

### 1.2 Project Requirements

#### Input Specification

Each input file contains one test case:

1. First line: `n1` (`1 <= n1 <= 2 x 10^5`), node count of `T1`.
2. Next `n1` lines: key `k` and parent index `p` of the i-th node.
3. Root node has parent index `-1`.
4. Then `T2` is given in the same format.
5. Last line: target `N` (same value range as key `k`).

Range constraints:

- `-2 x 10^9 <= k <= 2 x 10^9`
- `-2 x 10^9 <= N <= 2 x 10^9`

#### Output Specification

For each test case:

1. Print `true` if at least one solution exists, otherwise print `false`.
2. If solutions exist, print each solution as: `N = A + B`.
3. Print solutions in ascending order of `A`.
4. Print each equation only once.
5. Print preorder traversal sequences of `T1` and `T2` in the last two lines.
6. Values are separated by exactly one space, with no extra leading/trailing spaces.

## Chapter 2: Algorithm Specification

### 2.1 Main Data Structures

```c
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
```

- `Node` stores key value and two child pointers.
- Trees are built from an array of nodes and parent-index input.

### 2.2 Algorithm Pseudo-code

#### Main Procedure: Program Flow (`main`)

```text
MAIN():
   T1_nodes = NULL
   T2_nodes = NULL
   n1 = 0, n2 = 0

   T1 = READ_TREE(&T1_nodes, &n1)
   T2 = READ_TREE(&T2_nodes, &n2)
    if T1 == NULL OR T2 == NULL:
        if (T1 == NULL AND n1 != 0) OR (T2 == NULL AND n2 != 0):
            print "Invalid input for the Binary Search Tree!"
            exit

        print "false"
        if T1 != NULL:
            PRINT_RESULT(T1)
        else:
            print blank line

        if T2 != NULL:
            PRINT_RESULT(T2)
        else:
            print blank line

        if T1_nodes != NULL:
            free T1_nodes
        if T2_nodes != NULL:
            free T2_nodes
      exit

   now = -MAX_k - 1
   count = 0
   if CHECK(T1, &now, &count) == false OR count != n1:
      print "Invalid input for the Binary Search Tree!"
      free T1_nodes, T2_nodes
      exit

   now = -MAX_k - 1
   count = 0
   if CHECK(T2, &now, &count) == false OR count != n2:
      print "Invalid input for the Binary Search Tree!"
      free T1_nodes, T2_nodes
      exit

   read N
   if N < -MAX_k OR N > MAX_k:
      print "Invalid input for the target value N!"
      free T1_nodes, T2_nodes
      exit

   lastA = -MAX_k - 1
   found = FIND_SUM(T1, T2, N, false, &lastA)
   if found == false:
      print "false"

   PRINT_RESULT(T1)
   PRINT_RESULT(T2)

   free T1_nodes
   free T2_nodes
   exit
```

#### Algorithm A: Read and Build BST

```text
READ_TREE(node_array_ptr, n_ptr):
   read n
   store n into *n_ptr
    if n < 0 OR n > MAX_n:
      print "Invalid input for the number of nodes in the Binary Search Tree!"
      return NULL

    if n == 0:
        return NULL

   allocate node array with n elements
   if allocation fails:
      print "Memory allocation failed!"
      return NULL

   allocate parent index array with n elements
   if allocation fails:
      print "Memory allocation failed!"
      return NULL

   for i in [0, n-1]:
      read key[i], parent[i]
      initialize node[i].left = NULL, node[i].right = NULL
      if parent[i] < -1 OR parent[i] >= n:
         print "Invalid input for the parent node index!"
         free node array and parent index array
         return NULL
      if key[i] < -MAX_k OR key[i] > MAX_k:
         print "Invalid input for the node value!"
         free node array and parent index array
         return NULL

   root = BUILD_TREE(parent, node, n)
   free parent
   return root

BUILD_TREE(parent, node, n):
   root = NULL
   for i in [0, n-1]:
      if parent[i] == -1:
         root = &node[i]
      else if node[i].data < node[parent[i]].data:
         node[parent[i]].left = &node[i]
      else:
         node[parent[i]].right = &node[i]
   return root
```

#### Algorithm B: Validate BST and Count Nodes

```text
CHECK(tree, now, count):
   if tree == NULL: return true

   left_ok = CHECK(tree.left, now, count)
   if tree.data < *now: return false

   *now = tree.data
   *count = *count + 1

   right_ok = CHECK(tree.right, now, count)
   return left_ok AND right_ok
```

#### Algorithm C: Find and Print All Solutions

```text
FIND_SUM(T1, T2, N, found_flag, lastA):
   if T1 == NULL OR T2 == NULL: return false

   found_flag = FIND_SUM(T1.left, T2, N, found_flag, lastA) OR found_flag

   if T1.data != *lastA AND SEARCH_BST(T2, N - T1.data):
      if found_flag == false:
         print "true"
         found_flag = true

      print "N = T1.data + (N - T1.data)"
      *lastA = T1.data

   found_flag = FIND_SUM(T1.right, T2, N, found_flag, lastA) OR found_flag
   return found_flag

SEARCH_BST(root, x):
   if root == NULL: return false
   if root.data == x: return true
   if x < root.data: return SEARCH_BST(root.left, x)
   else: return SEARCH_BST(root.right, x)
```

#### Algorithm D: Print Preorder Traversal Without Extra Spaces

```text
PRINT_RESULT(tree):
   if tree == NULL: return false

   print tree.data without leading space
   PRINT_PREORDER_WITH_SPACE(tree.left)
   PRINT_PREORDER_WITH_SPACE(tree.right)
   print newline
   return true

PRINT_PREORDER_WITH_SPACE(node):
   if node == NULL: return false

   print " " + node.data
   PRINT_PREORDER_WITH_SPACE(node.left)
   PRINT_PREORDER_WITH_SPACE(node.right)
   return true
```

## Chapter 3: Testing Results

### 3.1 Test Case Table

| Case ID | Purpose (brief description) | Expected Result | Actual Behavior | Possible Cause of Bug (if failed) | Current Status |
|---|---|---|---|---|---|
| TC-01 | Basic case: multiple valid equations; verify ascending order of A | Print `true`; print three equations in ascending A; print preorder lines of T1 and T2 | Matches expected: `true`, 3 equations, then both preorder lines | - | pass |
| TC-02 | No-solution case | Print `false`; still print preorder lines of T1 and T2 | Matches expected: `false`, then both preorder lines | - | pass |
| TC-03 | Duplicate A values in T1 | Duplicate equation should appear only once | Matches expected: only one `20 = 10 + 10` line is printed | - | pass |
| TC-04 | Negative and zero values | Correct matching equations and correct traversal output format | Matches expected: prints `1 = -3 + 4` and `1 = 0 + 1`; traversal format correct | - | pass |
| TC-05 | Boundary values near +/- 2 x 10^9 | Program handles boundaries correctly without invalid output | Matches expected: three valid equations including extreme values | - | pass |
| TC-06 | Both trees are empty (`n=0`, `n=0`) | No error; print `false` and two blank traversal lines | Matches expected: `false` followed by two blank lines | - | pass |
| TC-07 | One tree is empty (`n=0`) | No error; print `false`; empty tree line is blank; non-empty tree printed in preorder | Matches expected: `false`, blank line for empty tree, `5 2 8` for non-empty tree | - | pass |
| TC-08 | Invalid parent index input | Print invalid parent-index message and stop as invalid BST input | Actual: `Invalid input for the parent node index!` then `Invalid input for the Binary Search Tree!` | Earlier mismatch was caused by missing early `return 0` in main invalid-input branch; fixed now | corrected |
| TC-09 | Invalid target N range | Print invalid-input message for target N and exit | Matches expected: `Invalid input for the target value N!` | - | pass |
| TC-10 | Invalid BST relationship (same-side child conflict) | Print invalid BST message during validation | Matches expected: `Invalid input for the Binary Search Tree!` | - | pass |
| TC-11 | Multiple roots in one tree | Print invalid BST message during validation | Matches expected: `Invalid input for the Binary Search Tree!` | - | pass |

### 3.2 Notes for Filling This Chapter

- Each test case should include: purpose, expected result, actual behavior, possible bug cause (if failed), and current status.
- `Current Status` must be one of: `pass`, `corrected`, `pending`.
- If `Actual Behavior` differs from `Expected Result`, explain the likely reason in `Possible Cause of Bug`.

## Chapter 4: Analysis and Comments

### 4.1 Time Complexity

- Building trees: `O(n1 + n2)`
- Validating BST by in-order traversal: `O(n1 + n2)`
- Searching solutions:
   - For each node in `T1`, one BST search in `T2`
   - Total: `O(n1 * h2)`
   - Worst case (skewed `T2`): `O(n1 * n2)`
   - Average case (balanced `T2`): `O(n1 * log n2)`

### 4.2 Space Complexity

- Node storage: `O(n1 + n2)`
- Recursion stack:
   - up to `O(h1 + h2)` (worst case can be linear in node count)

### 4.3 Comments and Possible Improvements

1. The current recursive implementation is clear but may risk deep recursion on skewed trees.
2. Iterative traversal/search can reduce recursion-depth risk.
3. A two-pointer method on two sorted sequences could optimize practical runtime for large data.
4. Input validation can be expanded to check structural issues such as multiple roots or cycles.

## Appendix: Source Code (in C)

- Source file: `main.c`
```C
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
    Tree T2=read_inport(&T2_node,&n2);    // Read T2 BST from input
    if(T1==NULL||T2==NULL)    // Check if T1 or T2 is empty
    {
        if((T1==NULL && n1!=0) || (T2==NULL && n2!=0))    // If either tree is NULL but expected to have nodes, print error
        {
            printf("Invalid input for the Binary Search Tree!\n");
            return 0;
        }
        // Get target sum N
        int N;
        scanf("%d",&N);
        printf("false\n");   // Print false if either tree is NULL
        if(T1!=NULL)    // If T1 is not NULL, print its preorder traversal
        {
            print_result(T1);
        }else{
            printf("\n");    // Print newline if T1 is NULL
        }
        if(T2!=NULL)    // If T2 is not NULL, print its preorder traversal
        {
            print_result(T2);
        }else{
            printf("\n");    // Print newline if T2 is NULL
        }
        // Free allocated memory
        if(T1_node!=NULL)
        {
            free(T1_node);
        }
        if(T2_node!=NULL)
        {
            free(T2_node);
        }
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
    if(T1_node!=NULL)
    {
        free(T1_node);
    }
    if(T2_node!=NULL)
    {
        free(T2_node);
    }
    return 0;
}

//Node** node - pointer to array of nodes for the BST
Tree read_inport(Node** node,int* num)//read the inport information of the Binary Search Tree,and return the Binary Search Tree
{
    // Get number of nodes
    int n;
    scanf("%d", &n);
    *num=n;    // Store number of nodes in provided pointer
    if(n<0||n>MAX_n)    // Validate n range
    {
        printf("Invalid input for the number of nodes in the Binary Search Tree!\n");
        return NULL;        // Return NULL indicating error
    }
    if(n==0)    // If n is 0, return NULL indicating empty tree
    {
        return NULL;
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
```

## Declaration

I hereby declare that all the work done in this project titled "A+B with Binary Search Trees" is of my independent effort.
