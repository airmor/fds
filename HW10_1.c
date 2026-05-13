#include <stdio.h>
#include <string.h>

int max_flow(int graph[1001][1001], int start, int end);

int main() {
    int start=1, end=2, N,num=0;
    int graph[1001][1001] = {0};  
    int menu[26][26][26] = {0};
    char sou[4];
    char des[4];
    int cap;
    scanf("%s %s %d\n", sou, des, &N);
    menu[sou[0]-'A'][sou[1]-'A'][sou[2]-'A'] = 1;
    menu[des[0]-'A'][des[1]-'A'][des[2]-'A'] = 2;
    num=2;
    for(int i=0;i<N;i++){
        scanf("%s %s %d\n", sou, des, &cap);
        if(menu[sou[0]-'A'][sou[1]-'A'][sou[2]-'A'] == 0){
            num++;
            menu[sou[0]-'A'][sou[1]-'A'][sou[2]-'A'] = num;
        }
        if(menu[des[0]-'A'][des[1]-'A'][des[2]-'A'] == 0){
            num++;
            menu[des[0]-'A'][des[1]-'A'][des[2]-'A'] = num;
        }
        graph[menu[sou[0]-'A'][sou[1]-'A'][sou[2]-'A']][menu[des[0]-'A'][des[1]-'A'][des[2]-'A']] += cap;
    }
    printf("%d\n", max_flow(graph, start, end));
    return 0;
}

int search(int graph[1001][1001], int start, int end, int parentd[1001]) {
    int visited[1001] = {0};
    visited[start] = 1;
    int queue[1001] = {0};
    int front = 0, rear = 0;
    queue[0] = start;
    while (front <= rear) {
        int current = queue[front++];
        for (int i = 0; i < 1001; i++) {
            if (!visited[i] && graph[current][i] > 0) {
                visited[i] = 1;
                parentd[i] = current;
                queue[++rear] = i;
                if (i == end) {
                    return 1; 
                }
            }
        }
    }
    return 0;

}

int max_flow(int graph[1001][1001], int start, int end) {
    int parentd[1001] = {0};
    int maxFlow = 0;
    while (search(graph, start, end, parentd)) {
        int pathFlow = 1e9; 
        for (int v = end; v != start; v = parentd[v]) {
            int u = parentd[v];
            if (graph[u][v] < pathFlow) {
                pathFlow = graph[u][v];
            }
        }
        for (int v = end; v != start; v = parentd[v]) {
            int u = parentd[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}