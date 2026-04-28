#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0
#define Max_Nv 1000
#define Max_Ne 100000
#define Max_K 100

typedef struct Node Node;
struct Node{
    int data;
    int distance;
    bool visited;
    int before;
    int* links;
};

