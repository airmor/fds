# Title of Project

A+B with Binary Search Trees (Project 2)

# Author's Name

[Fill in your name]

# Date

2026-04-01

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
struct Node {
      int data;
      struct Node* left;
      struct Node* right;
};
typedef struct Node* Tree;
```

- `Node` stores key value and two child pointers.
- Trees are built from an array of nodes and parent-index input.

### 2.2 Algorithm Pseudo-code

#### Algorithm A: Read and Build BST

```text
READ_TREE():
   read n
   validate n in [1, MAX_n]
   allocate node array and parent index array
   for i in [0, n-1]:
      read key[i], parent[i]
      validate key range and parent index range
      initialize node[i].left = NULL, node[i].right = NULL
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
   if T1 == NULL or T2 == NULL: return false
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

## Chapter 3: Testing Results

### 3.1 Test Case Table (Reserved)

| Case ID | Purpose | Input | Expected Output | Actual Output | Status |
|---|---|---|---|---|---|
| TC-01 | Basic: multiple solutions, ascending A | See test.md TC-01 input | See test.md TC-01 expected output |  | pending |
| TC-02 | No solution exists | See test.md TC-02 input | See test.md TC-02 expected output |  | pending |
| TC-03 | Duplicate A in T1 (deduplication) | See test.md TC-03 input | See test.md TC-03 expected output |  | pending |
| TC-04 | Negative and zero values | See test.md TC-04 input | See test.md TC-04 expected output |  | pending |
| TC-05 | Boundary values (±2e9) | See test.md TC-05 input | See test.md TC-05 expected output |  | pending |
| TC-06 | Invalid parent index | See test.md TC-06 input | See test.md TC-06 expected output |  | pending |
| TC-07 | Invalid target N | See test.md TC-07 input | See test.md TC-07 expected output |  | pending |
| TC-08 | Invalid BST structure (left child conflict) | See test.md TC-08 input | See test.md TC-08 expected output |  | pending |
| TC-09 | Multiple roots (two parent -1) | See test.md TC-09 input | See test.md TC-09 expected output |  | pending |
| TC-10 | Cycle exists, parent index valid | See test.md TC-10 input | See test.md TC-10 expected output |  | pending |

### 3.2 Notes for Filling This Chapter

- `Current Status` should use one of: `pass`, `corrected`, `pending`.
- If actual behavior differs from expected, fill in the likely bug cause.

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
- The appendix can directly paste full C code here when preparing final PDF submission.
- Ensure at least 30% lines are comments as required by the project rule.

## Declaration

I hereby declare that all the work done in this project titled "A+B with Binary Search Trees" is of my independent effort.
