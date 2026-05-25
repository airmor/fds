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

int is_in_part(int part[10][10],int part_num, int num, int vert){
    int a=0;
    for(int i=0;i<num;i++){
        if(part[part_num][i]==vert){
            a=1;
            break;
        }
    }
    return a;
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    int part[10][10]={0};
    int in_part[10]={0};
    int visited[10][11]={0};
    int queue[100000]={0};
    int part_num=0;
    int count=0;
    int front=0,rear=0;
    while(!is_visited(in_part,G->NumOfVertices)){
        for(int i=0;i<G->NumOfVertices;i++){
            if(in_part[i]==0){
                queue[rear++]=i;
                visited[i][0]=1;
                count=0;
                part[part_num++][count++]=i;
                in_part[i]=1;
                break;
            }
        }
        while(front<rear){
            int a=queue[front++];
            struct VNode* temp=G->Array[a]->Next;
            while(temp!=NULL){
                if(in_part[temp->Vert]==0){
                    if(visited[temp->Vert][0]==0){
                        queue[rear++]=temp->Vert;
                        visited[temp->Vert][0]=1;
                    }
                    
                        visited[temp->Vert][a+1]=1;
                    
                }
                else{
                    if(is_in_part(part,part_num-1,count,temp->Vert)){
                        for(int i=1;i<11;i++){
                            if(visited[temp->Vert][i]==1){
                                in_part[i-1]=1;
                                part[part_num-1][count++]=i-1;
                            }
                        }
                    }
                }
            }
            int hhh=1;
            while(hhh==1){
                hhh=0;
                for(int j=0;j<10;j++){
                if(is_in_part(part,part_num-1,count,j)){
                        for(int i=1;i<11;i++){
                            if(visited[j][i]==1){
                                in_part[i-1]=1;
                                part[part_num-1][count++]=i-1;
                            }
                        }
                    }}
            }
        }
        
    }
}