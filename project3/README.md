# Project 3 - Dijkstra Sequence Check

## Overview
This project checks whether each given vertex permutation is a valid Dijkstra sequence for a connected, undirected, weighted graph. The first vertex in each sequence is treated as the source. Ties are allowed: any vertex with the current minimum tentative distance can appear next.

## Input
- First line: Nv Ne
  - 1 <= Nv <= 1000, 1 <= Ne <= 100000
- Next Ne lines: u v w (undirected edge with weight w, 1 <= w <= 100)
- Next line: K (number of sequences, 1 <= K <= 100)
- Next K lines: a permutation of 1..Nv

## Output
For each sequence, print:
- Yes if it can be produced by Dijkstra's algorithm
- No otherwise

## Algorithm
For each query sequence:
1. Reset all vertex states and the min-heap.
2. Use the first vertex as the source (distance 0).
3. Insert all neighbors of the source into the min-heap.
4. For each remaining vertex in the sequence:
   - If its distance is greater than the current heap minimum, the sequence is invalid.
   - Otherwise remove it from the heap and relax its outgoing edges.
   - Ties are accepted because any vertex with the minimum distance is valid.

## Complexity
Per sequence:
- Time: O((Nv + Ne) log Nv)
- Space: O(Nv + Ne)

## Build and Run
Windows (PowerShell):

```powershell
gcc -Wall -Wextra -O0 .\code\main.c -o main.exe
.\main.exe < input.txt
```

Linux/macOS:

```bash
gcc -Wall -Wextra -O0 ./code/main.c -o main
./main < input.txt
```

## Example
Input:

```text
5 7
1 2 2
1 5 1
2 3 1
2 4 1
2 5 2
3 5 1
3 4 1
4
5 1 3 4 2
5 3 1 2 4
2 3 4 5 1
3 2 1 5 4
```

Output:

```text
Yes
Yes
Yes
No
```

## Development Environment
- Compiler: gcc 13.3.0
- System: Ubuntu 24.04 (WSL2)
