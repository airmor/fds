#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frozen;  // 0: current run, 1: next run
} Node;

static int node_less(const Node *a, const Node *b) {
    if (a->frozen != b->frozen) return a->frozen < b->frozen;
    return a->value < b->value;
}

static void heap_sift_up(Node *heap, int idx) {
    while (idx > 0) {
        int p = (idx - 1) >> 1;
        if (!node_less(&heap[idx], &heap[p])) break;
        Node t = heap[idx];
        heap[idx] = heap[p];
        heap[p] = t;
        idx = p;
    }
}

static void heap_sift_down(Node *heap, int size, int idx) {
    while (1) {
        int l = idx * 2 + 1;
        int r = l + 1;
        int best = idx;

        if (l < size && node_less(&heap[l], &heap[best])) best = l;
        if (r < size && node_less(&heap[r], &heap[best])) best = r;
        if (best == idx) break;

        Node t = heap[idx];
        heap[idx] = heap[best];
        heap[best] = t;
        idx = best;
    }
}

static void heap_build(Node *heap, int size) {
    for (int i = (size - 2) / 2; i >= 0; --i) {
        heap_sift_down(heap, size, i);
    }
}

static void heap_push(Node *heap, int *size, Node x) {
    heap[*size] = x;
    (*size)++;
    heap_sift_up(heap, (*size) - 1);
}

static Node heap_pop(Node *heap, int *size) {
    Node ret = heap[0];
    (*size)--;
    if (*size > 0) {
        heap[0] = heap[*size];
        heap_sift_down(heap, *size, 0);
    }
    return ret;
}

int main(void) {
    int N, M;

    while (scanf("%d %d", &N, &M) == 2) {
        Node *heap = (Node *)malloc((size_t)M * sizeof(Node));
        if (!heap) return 0;

        for (int i = 0; i < M; ++i) {
            scanf("%d", &heap[i].value);
            heap[i].frozen = 0;
        }

        int heap_size = M;
        int remaining = N - M;
        int line_first = 1;
        int last_output = 0;

        heap_build(heap, heap_size);

        while (heap_size > 0) {
            // If all records in memory belong to next run, start a new line/run.
            if (heap[0].frozen == 1) {
                putchar('\n');
                for (int i = 0; i < heap_size; ++i) heap[i].frozen = 0;
                heap_build(heap, heap_size);
                line_first = 1;
            }

            Node out = heap_pop(heap, &heap_size);

            if (!line_first) putchar(' ');
            printf("%d", out.value);
            line_first = 0;
            last_output = out.value;

            if (remaining > 0) {
                int x;
                scanf("%d", &x);
                Node in;
                in.value = x;
                in.frozen = (x < last_output) ? 1 : 0;
                heap_push(heap, &heap_size, in);
                remaining--;
            }
        }

        putchar('\n');
        free(heap);
    }

    return 0;
}