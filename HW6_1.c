#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Your function will be put here */

void PercolateUp( int p, PriorityQueue H ){
    if((H->Elements)[p/2]<(H->Elements)[p]){
        return;
    }
    ElementType tmp=(H->Elements)[p];
    (H->Elements)[p]=(H->Elements)[p/2];
    (H->Elements)[p/2]=tmp;
    PercolateUp(p/2,H );
    return;
}
void PercolateDown( int p, PriorityQueue H ){
    if((2*p>H->Size+1 || (H->Elements)[p]<(H->Elements)[2*p]) && (2*p+1>H->Size+1 || (H->Elements)[p]<(H->Elements)[2*p+1])){
        return;
    }
    if(2*p+1>H->Size+1 || (H->Elements)[2*p]<(H->Elements)[2*p+1]){

        ElementType tmp=(H->Elements)[p];
        (H->Elements)[p]=(H->Elements)[p*2];
        (H->Elements)[p*2]=tmp;
        PercolateDown( 2*p,H );
        return;
    }
        ElementType tmp=(H->Elements)[p];
        (H->Elements)[p]=(H->Elements)[p*2+1];
        (H->Elements)[p*2+1]=tmp;
        PercolateDown( 2*p+1,H );
    return;
}

PriorityQueue Initialize( int MaxElements ) {
    PriorityQueue H = (PriorityQueue) malloc( sizeof(struct HeapStruct) );
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements = (ElementType*) malloc( sizeof(ElementType) * MaxElements );
    return H;
}