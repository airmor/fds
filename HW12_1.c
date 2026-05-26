#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */

void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
    length*=2;
    int front1,front2,end1,end2;
    int turn=0;
    while(turn*length<N){
        if(turn*length+length/2>=N){
            front1=turn*length;
            front2=front1+length/2;
            end1=N-1;
            end2=N-1;
        }
        else if(turn*length+length>=N){
            front1=turn*length;
            front2=front1+length/2;
            end1=front2-1;
            end2=N-1;
        }
        else{
            front1=turn*length;
            front2=front1+length/2;
            end1=front2-1;
            end2=front2+length/2-1;
        }
        int i=front1;
        int j=front1;
        int k=front2;
        while(j<=end1||k<=end2){
            if(j<=end1&&k<=end2){
                if(list[j]<=list[k]){
                    sorted[i++]=list[j++];
                }
                else{
                    sorted[i++]=list[k++];
                }
            }
            else if(j<=end1){
                sorted[i++]=list[j++];
            }
            else{
                sorted[i++]=list[k++];
            }
        }
        turn++;
    }
}