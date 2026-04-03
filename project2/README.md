# A+B with Binary Search Trees

## Problem Description

Given two binary search trees T1 and T2, and an integer N, find all pairs (A, B) such that:
- A is a node value from T1
- B is a node value from T2  
- A + B = N

The solutions must be printed in ascending order of A values, and each equation should be printed only once.

## Input Format

The input consists of three parts:

1. **T1 (First Binary Search Tree)**:
   - First line: n1 (number of nodes in T1, 0 <= n1 <= 2x10^5)
   - Next n₁ lines: Each line contains two integers:
     - k (key value, -2×10⁹ ≤ k ≤ 2×10⁹)
     - p (parent node index, -1 ≤ p < n₁)
     - The root node has parent index -1
     - Nodes are indexed from 0 to n₁-1

2. **T2 (Second Binary Search Tree)**:
   - Same format as T1
   - First line: n2 (number of nodes in T2, 0 <= n2 <= 2x10^5)
   - Next n₂ lines: key value and parent index for each node

3. **Target Value**:
   - Last line: N (target sum, -2×10⁹ ≤ N ≤ 2×10⁹)

## Output Format

1. First line: `true` if at least one solution exists, otherwise `false`
2. For each solution (if any), print one line in the format: `N = A + B`
   - Solutions are printed in ascending order of A values
   - Each equation is printed only once (no duplicates)
3. Next line: Preorder traversal of T1 (space-separated values)
   - If T1 is empty, this line is blank
4. Last line: Preorder traversal of T2 (space-separated values)
   - If T2 is empty, this line is blank

Special behavior in current implementation:
- If either tree is empty and this is valid input (n=0), the program prints false and exits after printing traversal lines.
- If a tree read fails while n is not 0, the program prints Invalid input for the Binary Search Tree! and exits.

**Note**: No extra spaces at the beginning or end of any line.

## Binary Search Tree Properties

A Binary Search Tree (BST) is recursively defined as:
- The left subtree of a node contains only nodes with keys **less than** the node's key
- The right subtree of a node contains only nodes with keys **greater than or equal to** the node's key
- Both the left and right subtrees must also be binary search trees

## Program Structure

The program (`main.c`) consists of the following functions:

### Main Functions
- `read_inport()`: Reads BST information from input and allocates memory
- `build_tree()`: Constructs BST from parent index array
- `find_sum_is_N()`: Finds all A in T1 and B in T2 such that A + B = N
- `find_n_in_tree()`: Searches for a value in a BST
- `print_preorder_traversal()`: Prints preorder traversal with proper spacing
- `print_result()`: Prints the complete preorder traversal result

### Key Features
- Memory management with proper allocation and deallocation
- Input validation for node count, parent indices, and key values
- Supports empty tree input (n=0)
- Recursive tree traversal algorithms
- Efficient BST search (O(h) time complexity)
- Avoids duplicate solution printing

## Algorithm

1. **Tree Construction**:
   - Read number of nodes and allocate memory
   - If n is 0, treat as an empty tree (not an error)
   - Read each node's key and parent index
   - Validate input ranges
   - Build tree by linking nodes based on parent indices and BST properties

2. **Early Branch for Empty/Invalid Trees**:
   - If T1 or T2 is NULL:
     - If corresponding n is not 0, print Invalid input for the Binary Search Tree! and exit
     - Otherwise print false, print traversal lines (blank line for empty tree), and exit

3. **Solution Search**:
   - Perform inorder traversal of T1 (ascending order of values)
   - For each node A in T1:
     - Calculate B = N - A
     - Search for B in T2 using BST search
     - If found and not a duplicate, print the solution
   - Track the last printed A to avoid duplicates

4. **Output**:
   - Print `true`/`false` based on solution existence
   - Print all solutions in required format
   - Print preorder traversals of both trees

## Compilation and Execution

### Compilation
```bash
gcc -Wall -Wextra -O0 -o main main.c
```

### Execution
```bash
./main
```

On Windows (PowerShell), you can run:

```powershell
gcc -Wall -Wextra -O0 main.c -o main.exe
.\main.exe
```

### Example
**input_1**
```
8
12 2
16 5
13 4
18 5
15 -1
17 4
14 2
18 3
7
20 -1
16 0
25 0
13 1
18 1
21 2
28 2
36
```
**output_1**
```
true
36 = 15 + 21
36 = 16 + 20
36 = 18 + 18
15 13 12 14 17 16 18 18
20 16 13 18 25 21 28
```
**input_2**
```
5
10 -1
5 0
15 0
2 1
7 1
3
15 -1
10 0
20 0
40
```
**output_2**
```
false
10 5 2 7 15
15 10 20
```

## Implementation Details

### Constants
- `MAX_n = 200000`: Maximum number of nodes
- `MAX_k = 2000000000`: Maximum absolute key value

### Data Structures
```c
struct Node {
    int data;           // Key value
    struct Node* left;  // Left child
    struct Node* right; // Right child
};

typedef struct Node* Tree;
```

### Error Handling
- Invalid node count range
- Invalid parent index
- Invalid key value range
- Invalid BST structure detected by in-order validation and node counting
- Memory allocation failure
- Invalid target value N
- Empty tree is treated as valid input (n=0)

## Complexity Analysis

- **Time Complexity**: $O(n_1 × h_2)$ where h₂ is the height of T2
  - In worst case (skewed trees): $O(n_1 × n_2)$
  - In average case (balanced trees): $O(n_1 × \log{n_2})$
- **Space Complexity**: $O(n_1 + n_2)$ for storing the trees

## Notes

1. The program does not assume valid BST input; it validates and may reject malformed input
2. Parent indices are 0-based
3. The root node has parent index -1
4. All input values should be within specified ranges (-2,000,000,000 to 2,000,000,000)
5. The program handles large inputs (up to 200,000 nodes per tree)
6. Empty trees (n=0) are valid and produce blank traversal lines
7. If tree structure is invalid or reachable node count mismatches n, output is Invalid input for the Binary Search Tree!

## Development Environment
- Compiler: gcc 13.3.0
- System: Ubuntu 24.04 (WSL2)