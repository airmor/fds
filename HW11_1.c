#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */

int is_visited(int visited[], int num){
    int a=1;
    for(int i=0;i<num;i++){
        if(visited[i]==0){
            a=0;
            break;
        }    }
    return a;
}

int is_in_part(int part[MaxVertices][MaxVertices], int part_num, int vert){
    int a=0;
    if(part[part_num][vert]==1){
        a=1;
    }
    return a;
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    int part[MaxVertices][MaxVertices]={0};
    int in_part[MaxVertices]={0};
    int visited[MaxVertices][MaxVertices+1]={0};
    int queue[100000]={0};
    int part_num=0;
    int count=0;
    int front=0,rear=0;
    while(!is_visited(in_part,G->NumOfVertices)){
        for(int i=0;i<G->NumOfVertices;i++){
            for(int j=0;j<G->NumOfVertices+1;j++){
                visited[i][j]=0;
            }
        }
        for(int i=0;i<G->NumOfVertices;i++){
            if(in_part[i]==0){
                queue[rear++]=i;
                visited[i][0]=1;
                count=0;
                part[part_num++][i]=1;
                in_part[i]=1;
                break;
            }
        }
        while(front<rear){
            int vert=queue[front++];
            PtrToVNode ptr=G->Array[vert];
            while(ptr){
                visited[vert][0]=1;
                visited[vert][ptr->Vert+1]=1;
                if(visited[ptr->Vert][0]==0){
                    queue[rear++]=ptr->Vert;
                    visited[ptr->Vert][0]=1;
                }
                ptr=ptr->Next;
            }
        }
        int note=1;
        while(note){
            note=0;
            for(int i=0;i<G->NumOfVertices;i++){
                if(visited[i][0]==1 && is_in_part(part, part_num-1, i)==0){
                    for(int j=0;j<G->NumOfVertices;j++){
                        if(visited[i][j+1]==1 && is_in_part(part, part_num-1, j)==1){
                            part[part_num-1][i]=1;
                            in_part[i]=1;
                            note=1;
                        }
                    }
                }
            }
        }

        for(int i=0;i<G->NumOfVertices;i++){
            if(part[part_num-1][i]==1){
                visit(i);
            }
        }
        printf("\n");
        
    }
    return;
}