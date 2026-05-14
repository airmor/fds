#include <stdio.h>

struct imformation {
    int num;
    int cost;
};

int N,M;

struct imformation min(int list[501]){
    int min_cost = 1073741824;
    int min_num = 0;
    int num = 0;
    for(int i=0; i<N+1; i++) {
        if(list[i] != 0 && list[i] < min_cost) {
            min_cost = list[i];
            min_num = i;
            num=1;
        }
        else if(list[i] != 0 && list[i] == min_cost) {
            num++;
        }
    }
    struct imformation result;
    result.num = num;
    result.cost = min_num;
    return result;
}

struct imformation build(int graph[501][501], int Nm, int visited[501]) {
    int total_cost = 0;
    int num = 1;
    int list[501]= {0};
    visited[Nm] = 1;
    for(int i=0; i<N+1; i++) {
        if(graph[Nm][i] != 0 && visited[i] == 0) {
            list[i] = graph[Nm][i];
        }
    }
    struct imformation result = min(list);
    while(result.num != 0) {
        num *= result.num;
        total_cost += list[result.cost];
        visited[result.cost] = 1;
        list[result.cost] = 0;
        for(int i=0; i<N+1; i++) {
            if(graph[result.cost][i] != 0 && visited[i] == 0) {
                if(list[i] == 0 || list[i] > graph[result.cost][i]) {
                    list[i] = graph[result.cost][i];
                }
                else if(list[i] == graph[result.cost][i]) {
                    num++;
                }
            }
        }
        result = min(list);
        
    }
    struct imformation result2;
    result2.num = num;
    result2.cost = total_cost;
    return result2;

}

int main() {
    
    scanf("%d %d", &N, &M);
    int arr[501][501];
    for(int i=0; i<M; i++) {
        int a,b,cost;
        scanf("%d %d %d", &a, &b, &cost);
        if(arr[a][b] == 0 || arr[a][b] > cost) {
            arr[a][b] = cost;
            arr[b][a] = cost;
        }
    }
    int visited[501] = {0};
    int part=1;
    int is_connected = 1;
    struct imformation result = build(arr, 1, visited);
    for(int i=1; i<=N; i++) {
        if(visited[i] == 0) {
            part ++;
            is_connected = 0;
            break;
        }
    }
    if(is_connected == 1) {
        printf("%d\n", result.cost);
        if(result.num != 1) {
            printf("No\n");
        }
        else {
            printf("Yes\n");
        }
    }
    else {
        while(is_connected == 0) {
            for(int i=1; i<=N; i++) {
                if(visited[i] == 0) {
                    part++;
                    struct imformation result2 = build(arr, i, visited);
                    break;
                }
            }
            is_connected = 1;
            for(int i=1; i<=N; i++) {
                if(visited[i] == 0) {
                    is_connected = 0;
                    break;
                }
            }
        }
        printf("No MST\n%d\n", part-1);
    }
    return 0;
}

