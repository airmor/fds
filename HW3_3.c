#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frozen;
} Node;

int is_less(Node *a, Node *b) {
    if (a->frozen != b->frozen) return a->frozen < b->frozen;
    return a->value < b->value;
}

void heap_sift_up(Node *heap, int idx) {
    while (idx > 1) {
        int p = idx / 2;
        if (!is_less(&heap[idx], &heap[p])) break;
        Node t = heap[idx];
        heap[idx] = heap[p];
        heap[p] = t;
        idx = p;
    }
}

void heap_sift_down(Node *heap, int size, int idx) {
    Node now=heap[idx];
    int p=idx;
    while (1) {
        int child = p * 2;
        if (child > size) break;
        if (child + 1 <= size && is_less(&heap[child + 1], &heap[child])) child++;
        if (!is_less(&heap[child], &now)) break;
        heap[p] = heap[child];
        p = child;
    }    
    heap[p] = now;
}

void heap_build(Node *heap, int size) {
    for (int i = size / 2; i > 0; --i) {
        heap_sift_down(heap, size, i);
    }
}

void push(Node *heap, int *size, Node new) {
    (*size)++;
    heap[*size] = new;
    heap_sift_up(heap, *size);
}



Node pop(Node *heap, int *size) {
    Node ret = heap[1];
    (*size)--;
    if (*size > 0) {
        heap[1] = heap[*size+1];
        heap_sift_down(heap, *size, 1);
    }
    return ret;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
        Node *heap = (Node *)malloc((M+1) * sizeof(Node));

        for (int i = 1; i <= M; ++i) {
            if(N>0) scanf("%d", &heap[i].value);
            N--;
            heap[i].frozen = 0;
        }


        heap_build(heap, M);
        int heap_size = M;
        {
            Node first_out = pop(heap, &heap_size);
            printf("%d", first_out.value);
            
            if(N > 0){
                Node new;
                scanf("%d", &new.value);
                new.frozen = (new.value < first_out.value) ? 1 : 0;
                push(heap, &heap_size, new);
                N--;
            }
        }
        while (heap_size > 0) {
            if (heap[1].frozen == 1) {
                printf("\n");
                for (int i = 1; i <= heap_size; i++)
                {
                    heap[i].frozen = 0;
                }
                heap_build(heap, heap_size);
                if(heap_size == 0){
                    continue;
                }
                Node first_out = pop(heap, &heap_size);
                printf("%d", first_out.value);
                if(N == 0){
                    continue;
                }
                Node new;
                scanf("%d", &new.value);
                new.frozen = (new.value < first_out.value) ? 1 : 0;
                push(heap, &heap_size, new);
                N--;
                if(M==1){
                    continue;
                }
            }

            Node out = pop(heap, &heap_size);

            printf(" %d", out.value);

            if(N == 0){
                continue;
            }
            Node new;
            scanf("%d", &new.value);
            new.frozen = (new.value < out.value) ? 1 : 0;
            push(heap, &heap_size, new);
            N--;
        }


        printf("\n");
        free(heap);


    return 0;
}