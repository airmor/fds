// Include stdio for scanf and printf.
#include <stdio.h>
// Include stdlib for malloc and free.
#include <stdlib.h>
// Include string.h for memset.
#include <string.h>

// Use int as a simple boolean type.
#define bool int
// Define the true literal as 1.
#define true 1
// Define the false literal as 0.
#define false 0

// Maximum number of vertices allowed by the problem.
#define Max_Nv 1000
// Maximum number of edges allowed by the problem.
#define Max_Ne 100000
// Maximum number of query sequences allowed by the problem.
#define Max_K 100
// Maximum edge weight allowed by the problem.
#define Max_Cost 100

// Vertex record used by the graph and the heap.
typedef struct Node Node;
// Edge record used by the adjacency lists.
typedef struct Edge Edge;
// Heap record used to track candidate vertices.
typedef struct MinHeap MinHeap;

// Each vertex stores the current tentative distance, visit state,
// predecessor, heap position, and adjacency-list head.
struct Node{
    int distance;   // Current shortest distance estimate.
    bool visited;   // Whether this vertex has been discovered.
    int before;     // Previous vertex on the current shortest path.
    int index;      // Current heap position of this vertex.
    Edge* edges;    // Dummy head for the adjacency list.
};

// Each edge stores the destination vertex, its cost, and the next edge.
struct Edge{
    int data;          // Adjacent vertex id.
    int cost;          // Edge weight.
    struct Edge* next;  // Next edge in the adjacency list.
};

// Min-heap of vertex ids used to simulate Dijkstra's frontier.
struct MinHeap{
    int size;      // Number of valid elements currently in the heap.
    int* indexes;  // Vertex ids arranged according to heap order.
};



// Build all edges and link them into adjacency lists.
Node* CreatEdges(Node* nodes,int Nv,int Ne);

// Free the adjacency lists and the vertex array.
Node* FreeNodes(Node* nodes,int Nv);

// Reset vertex and heap state before checking one query sequence.
Node* Initial(Node* nodes,MinHeap* minHeap,int Nv);

// Restore the min-heap property by moving a node upward.
MinHeap* PercolateUp(Node* nodes,MinHeap* minHeap,int Nv,int index);

// Restore the min-heap property by moving a node downward.
MinHeap* PercolateDown(Node* nodes,MinHeap* minHeap,int Nv,int index);

// Insert one vertex into the heap.
MinHeap* Insert(Node* nodes,MinHeap* minHeap,int Nv,int node);

// Delete one vertex from the heap by its heap index.
MinHeap* Delete(Node* nodes,MinHeap* minHeap,int Nv,int index);

// Check whether one permutation is a valid Dijkstra sequence.
bool IsDijkstraSequence(Node* nodes,MinHeap* minHeap,int Nv);

int main(){
    int Nv, Ne;                                             // Number of vertices and edges.
    scanf("%d %d",&Nv,&Ne);                                // Read graph size.
    if(Nv>Max_Nv || Nv<1 || Ne>Max_Ne || Ne<1){             // Validate graph size.
        printf("Invalid input\n");                         // Reject out-of-range graph data.
        return 0;                                           // Exit immediately on invalid input.
    }

    // Allocate the vertex array; index 1..Nv is used directly.
    Node* nodes=(Node*)malloc(sizeof(Node)*(Nv+1));         // Allocate storage for all vertices.
    if(nodes==NULL){                                        // Check whether allocation succeeded.
        printf("Memory allocation failed\n");              // Report allocation failure.
        return 0;                                           // Stop because the graph cannot be built.
    }

    // Read all edges and build the adjacency lists.
    nodes=CreatEdges(nodes,Nv,Ne);                          // Build the graph from input.
    if(nodes==NULL)return 0;                                // Abort if graph construction failed.

    // The min-heap stores the current Dijkstra frontier.
    MinHeap* minHeap=(MinHeap*)malloc(sizeof(MinHeap));     // Allocate the heap container.
    if(minHeap==NULL){                                      // Check whether allocation succeeded.
        printf("Memory allocation failed\n");              // Report allocation failure.
        FreeNodes(nodes,Nv);                                // Release graph memory before exiting.
        return 0;                                           // Stop because the heap cannot be built.
    }
    minHeap->size=0;                                        // Start with an empty heap.
    minHeap->indexes=(int*)malloc(sizeof(int)*(Nv+1));      // Allocate heap storage.
    if(minHeap->indexes==NULL){                             // Check whether allocation succeeded.
        printf("Memory allocation failed\n");              // Report allocation failure.
        FreeNodes(nodes,Nv);                                // Release graph memory before exiting.
        free(minHeap);                                      // Release the heap container.
        return 0;                                           // Stop because the heap array cannot be built.
    }

    int K;                                                  // Number of query sequences.
    scanf("%d",&K);                                         // Read the number of queries.
    if(K>Max_K || K<1){                                     // Validate query count.
        printf("Invalid input\n");                         // Reject out-of-range query count.
        FreeNodes(nodes,Nv);                                // Release graph memory before exiting.
        free(minHeap->indexes);                             // Release heap storage.
        free(minHeap);                                      // Release the heap container.
        return 0;                                           // Stop because the query count is invalid.
    }

    // Check every query sequence independently.
    for(int i=0;i<K;i++){                                   // Process each query sequence once.
        Initial(nodes,minHeap,Nv);                          // Reset all vertex and heap state.
        if(IsDijkstraSequence(nodes,minHeap,Nv)){           // Test whether the sequence is valid.
            printf("Yes\n");                                // Print success for a valid sequence.
        }
        else{                                               // The sequence failed the Dijkstra check.
            printf("No\n");                                 // Print failure for an invalid sequence.
        }
    }

    // Release all allocated memory before exiting.
    FreeNodes(nodes,Nv);                                    // Free the graph structure.
    if(minHeap->indexes==NULL){                             // Preserve the original cleanup branch.
        printf("Memory allocation failed\n");              // Report a memory failure message.
        free(minHeap);                                      // Release the heap container.
        return 0;                                           // Exit on failure.
    }
    free(minHeap->indexes);                                 // Release the heap array.
    free(minHeap);                                          // Release the heap container.
    return 0;                                               // Normal exit.
}

Node* CreatEdges(Node* nodes,int Nv,int Ne){
    int a,b,cost;                                           // Edge endpoints and weight.

    // Clear the vertex array so every field starts from a known state.
    memset(nodes,0,sizeof(Node)*(Nv+1));                    // Initialize all vertex records to zero.

    // Create a dummy head node for each adjacency list.
    for(int i=1;i<=Nv;i++){                                 // Visit every vertex once.
        nodes[i].edges=(Edge*)malloc(sizeof(Edge));         // Allocate a dummy head for the adjacency list.
        if(nodes[i].edges==NULL){                           // Check whether allocation succeeded.
            printf("Memory allocation failed\n");          // Report allocation failure.
            FreeNodes(nodes,Nv);                            // Free everything allocated so far.
            return NULL;                                    // Signal failure to the caller.
        }
        nodes[i].edges->next=NULL;                          // The dummy head initially points to nothing.
    }

    // Read each undirected edge and append it to both endpoints.
    for(int i=1;i<=Ne;i++){                                 // Process every input edge.
        int temp=scanf("%d %d %d",&a,&b,&cost);            // Read one edge record.
        if(a>Nv || a<1 || b>Nv || b<1 || cost<0 || cost>Max_Cost || temp!=3){ // Validate the edge record.
            printf("Invalid input\n");                     // Reject malformed edge data.
            FreeNodes(nodes,Nv);                            // Free all partially built graph data.
            return NULL;                                    // Signal failure to the caller.
        }

        // Store a -> b.
        Edge* a_NewEdge=(Edge*)malloc(sizeof(Edge));        // Allocate the forward adjacency node.
        if(a_NewEdge==NULL){                                // Check whether allocation succeeded.
            printf("Memory allocation failed\n");          // Report allocation failure.
            FreeNodes(nodes,Nv);                            // Free all partially built graph data.
            return NULL;                                    // Signal failure to the caller.
        }
        a_NewEdge->data=b;                                  // Store the destination vertex.
        a_NewEdge->cost=cost;                               // Store the edge weight.
        a_NewEdge->next=NULL;                               // This node is currently the tail.

        // Store b -> a.
        Edge* b_NewEdge=(Edge*)malloc(sizeof(Edge));        // Allocate the reverse adjacency node.
        if(b_NewEdge==NULL){                                // Check whether allocation succeeded.
            printf("Memory allocation failed\n");          // Report allocation failure.
            FreeNodes(nodes,Nv);                            // Free all partially built graph data.
            return NULL;                                    // Signal failure to the caller.
        }
        b_NewEdge->data=a;                                  // Store the destination vertex.
        b_NewEdge->cost=cost;                               // Store the edge weight.
        b_NewEdge->next=NULL;                               // This node is currently the tail.

        // Append the new edge to vertex a.
        Edge* current=nodes[a].edges;                       // Start from the dummy head of vertex a.
        while(current->next!=NULL){                         // Walk to the end of a's adjacency list.
            current=current->next;                          // Advance to the next edge.
        }
        current->next=a_NewEdge;                            // Link the new forward edge at the tail.

        // Append the reverse edge to vertex b.
        current=nodes[b].edges;                             // Start from the dummy head of vertex b.
        while(current->next!=NULL){                         // Walk to the end of b's adjacency list.
            current=current->next;                          // Advance to the next edge.
        }
        current->next=b_NewEdge;                            // Link the new reverse edge at the tail.
    }
    return nodes;                                           // Return the fully built graph.
}

Node* FreeNodes(Node* nodes,int Nv){
    // Free every adjacency list, including the dummy head node.
    for(int i=1;i<=Nv;i++){                                 // Visit each vertex in order.
        Edge* current=nodes[i].edges;                       // Start from the head of the adjacency list.
        while(current!=NULL){                               // Traverse the whole list.
            Edge* temp=current;                             // Save the current node before freeing it.
            current=current->next;                          // Advance to the next node.
            free(temp);                                     // Release the current edge node.
        }
    }
    free(nodes);                                            // Release the vertex array itself.
    return NULL;                                            // Return NULL for convenient cleanup assignment.
}

Node* Initial(Node* nodes,MinHeap* MinHeap,int Nv){
    // Reset every vertex to its initial Dijkstra state.
    for(int i=1;i<=Nv;i++){                                 // Visit each vertex once.
        nodes[i].distance=Max_Cost*Max_Nv+1;               // Set distance to a safe infinity value.
        nodes[i].before=0;                                 // Clear predecessor information.
        nodes[i].index=0;                                  // Clear heap position information.
        nodes[i].visited=false;                            // Mark the vertex as undiscovered.
    }
    memset(MinHeap->indexes,0,sizeof(int)*(Nv+1));         // Clear all heap slots.
    MinHeap->size=0;                                       // Reset heap size to zero.
    return nodes;                                          // Return the reset vertex array.
}

MinHeap* PercolateUp(Node* nodes,MinHeap* minHeap,int Nv,int index){
    int parent=index/2;                                    // Compute the parent index.
    // Swap upward until the parent is no larger than the current node.
    if(parent>=1 && nodes[minHeap->indexes[index]].distance<nodes[minHeap->indexes[parent]].distance){ // Compare child and parent distances.
        int temp=minHeap->indexes[index];                  // Save the current vertex id.
        minHeap->indexes[index]=minHeap->indexes[parent];  // Move the parent down.
        minHeap->indexes[parent]=temp;                     // Move the current vertex up.
        nodes[minHeap->indexes[index]].index=index;        // Update the moved vertex's heap position.
        nodes[minHeap->indexes[parent]].index=parent;      // Update the other moved vertex's heap position.
        return PercolateUp(nodes,minHeap,Nv,parent);       // Continue bubbling upward.
    }
    return minHeap;                                        // Heap order is already correct.
}

MinHeap* PercolateDown(Node* nodes,MinHeap* minHeap,int Nv,int index){
    // Stop when the current node has no child.
    if(index*2>minHeap->size)return minHeap;               // No children means the heap order is satisfied.

    // Handle the one-child case separately.
    if(index*2+1>minHeap->size){                           // Only a left child exists.
        if(nodes[minHeap->indexes[index]].distance>nodes[minHeap->indexes[index*2]].distance){ // Compare parent and left child.
            int temp=minHeap->indexes[index];              // Save the current vertex id.
            minHeap->indexes[index]=minHeap->indexes[index*2]; // Move the left child up.
            minHeap->indexes[index*2]=temp;                // Move the parent down.
            nodes[minHeap->indexes[index]].index=index;    // Update the moved vertex's heap position.
            nodes[minHeap->indexes[index*2]].index=index*2; // Update the other moved vertex's heap position.
            return PercolateDown(nodes,minHeap,Nv,index*2); // Continue bubbling downward.
        }
        return minHeap;                                    // Heap order is already correct.
    }

    // Pick the smaller child and swap downward if necessary.
    int left=index*2;                                      // Left child index.
    int right=index*2+1;                                   // Right child index.
    int min;                                               // Index of the smaller child.
    if(nodes[minHeap->indexes[left]].distance<=nodes[minHeap->indexes[right]].distance){ // Compare child distances.
        min=left;                                          // Left child is smaller or equal.
    }else{
        min=right;                                         // Right child is smaller.
    }
    if(nodes[minHeap->indexes[index]].distance>nodes[minHeap->indexes[min]].distance){ // Compare parent and smaller child.
        int temp=minHeap->indexes[index];                  // Save the current vertex id.
        minHeap->indexes[index]=minHeap->indexes[min];     // Move the smaller child up.
        minHeap->indexes[min]=temp;                        // Move the parent down.
        nodes[minHeap->indexes[index]].index=index;        // Update the moved vertex's heap position.
        nodes[minHeap->indexes[min]].index=min;            // Update the other moved vertex's heap position.
        return PercolateDown(nodes,minHeap,Nv,min);        // Continue bubbling downward.
    }
    return minHeap;                                        // Heap order is already correct.
}

MinHeap* Insert(Node* nodes,MinHeap* minHeap,int Nv,int node){
    // Append the new vertex at the end and bubble it upward.
    minHeap->size++;                                       // Increase heap size first.
    minHeap->indexes[minHeap->size]=node;                  // Place the new vertex at the tail.
    nodes[node].index=minHeap->size;                       // Record the heap position in the vertex.
    return PercolateUp(nodes,minHeap,Nv,minHeap->size);    // Restore heap order from the new slot.
}

MinHeap* Delete(Node* nodes,MinHeap* minHeap,int Nv,int index){
    // Move the last heap element into the deleted slot, then restore order.
    minHeap->indexes[index]=minHeap->indexes[minHeap->size]; // Copy the last heap element into the gap.
    nodes[minHeap->indexes[index]].index=index;             // Update the moved vertex's heap position.
    minHeap->size--;                                        // Shrink the heap.
    PercolateDown(nodes,minHeap,Nv,index);                  // Restore order from the affected slot.
    minHeap->indexes[minHeap->size+1]=0;                    // Clear the stale tail slot.
    return minHeap;                                         // Return the updated heap.
}

bool IsDijkstraSequence(Node* nodes,MinHeap* minHeap,int Nv){
    int source;                                             // Source vertex from the query sequence.
    scanf("%d",&source);                                    // Read the source vertex.

    // The first vertex in the sequence is the source.
    nodes[source].distance=0;                               // The source distance is zero.
    nodes[source].visited=true;                              // Mark the source as discovered.

    // Initialize the frontier with the source's adjacent vertices.
    Edge* current=nodes[source].edges->next;                 // Start from the first real adjacency node.
    while(current!=NULL){                                    // Traverse all neighbors of the source.
        nodes[current->data].distance=current->cost;         // Set the initial tentative distance.
        nodes[current->data].before=source;                  // Set the source as predecessor.
        nodes[current->data].visited=true;                   // Mark the neighbor as discovered.
        Insert(nodes,minHeap,Nv,current->data);              // Insert the neighbor into the heap.
        current=current->next;                               // Move to the next neighbor.
    }

    // Validate the remaining vertices against the expected Dijkstra order.
    for(int i=2;i<=Nv;i++){                                  // Check the remaining vertices one by one.
        int num;                                             // Vertex id read from the query sequence.
        scanf("%d",&num);                                    // Read the next vertex in the sequence.

        // The next vertex must have the same distance as the heap minimum.
        if(nodes[num].distance>nodes[minHeap->indexes[1]].distance){ // Compare against the current minimum.
            // Consume the rest of the query to keep input aligned.
            for(i=i+1;i<=Nv;i++){                            // Skip the remaining vertex ids.
                scanf("%d",&num);                           // Read and discard one vertex id.
            }
            return false;                                    // The sequence is not a valid Dijkstra order.
        }
        else{                                                // The chosen vertex matches the heap minimum distance.
            Delete(nodes,minHeap,Nv,nodes[num].index);       // Remove it from the heap.
        }

        // Relax every edge out of the selected vertex.
        current=nodes[num].edges->next;                      // Start from the first real adjacency node.
        while(current!=NULL){                                // Traverse all neighbors of the selected vertex.
            if(nodes[current->data].visited==false){         // First time discovering this vertex.
                nodes[current->data].visited=true;           // Mark it as discovered.
                nodes[current->data].distance=nodes[num].distance+current->cost; // Set its tentative distance.
                nodes[current->data].before=num;             // Record the predecessor.
                Insert(nodes,minHeap,Nv,current->data);      // Push it into the heap.
            }
            else if(nodes[current->data].distance>nodes[num].distance+current->cost){ // Found a shorter path.
                nodes[current->data].distance=nodes[num].distance+current->cost;     // Update the distance.
                nodes[current->data].before=num;            // Update the predecessor.
                PercolateUp(nodes,minHeap,Nv,current->data); // Restore heap order after the decrease.
            }
            current=current->next;                           // Move to the next adjacency node.
        }
    }
    return true;                                             // The sequence satisfies Dijkstra's rule.
}