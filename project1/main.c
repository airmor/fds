#include <stdio.h>
#include "BinarySearch_iterative.h"
#include "BinarySearch_recursive.h"
#include "SequentialSearch_iterative.h"
#include "SequentialSearch_recursive.h"
#include <time.h>
#ifndef K_BSI
#define K_BSI 1
#endif
#ifndef K_BSR
#define K_BSR 1
#endif
#ifndef K_SSI
#define K_SSI 1
#endif
#ifndef K_SSR
#define K_SSR 1
#endif
#ifndef N
#define N 0
#endif

clock_t start,stop; /* clock t is a built-in type for processor time (ticks) */
double BSI_time; //records the run time (seconds) of Binary Search Iterative
double BSR_time; //records the run time (seconds) of Binary Search Recursive
double SSI_time; //records the run time (seconds) of Sequential Search Iterative
double SSR_time; //records the run time (seconds) of Sequential Search Recursive


int main() {
    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }
    int target = N; // Set the target
    #if BSI // 计时并测试二分查找（迭代版）
    start = clock(); // Start the timer
    for (int i = 0; i < K_BSI; i++) {
        BinarySearchIterative(arr, N, target);
    }
    stop = clock(); // Stop the timer
    BSI_time = (double)(stop - start) / CLOCKS_PER_SEC; // Calculate the run time (seconds)
    printf("Binary Search Iterative: %f seconds\n", BSI_time);
    #endif
    #if BSR // 计时并测试二分查找（递归版）
    start = clock(); // Start the timer
    for (int i = 0; i < K_BSR; i++) {
        BinarySearchRecursive(arr, N, target);
    }
    stop = clock(); // Stop the timer
    BSR_time = (double)(stop - start) / CLOCKS_PER_SEC; // Calculate the run time (seconds)
    printf("Binary Search Recursive: %f seconds\n", BSR_time);
    #endif
    #if SSI // 计时并测试顺序查找（迭代版）
    start = clock(); // Start the timer
    for (int i = 0; i < K_SSI; i++) {
        SequentialSearchIterative(arr, N, target);
    }
    stop = clock(); // Stop the timer
    SSI_time = (double)(stop - start) / CLOCKS_PER_SEC; // Calculate the run time (seconds)
    printf("Sequential Search Iterative: %f seconds\n", SSI_time);
    #endif
    #if SSR // 计时并测试顺序查找（递归版）
    start = clock(); // Start the timer
    for (int i = 0; i < K_SSR; i++) {
        SequentialSearchRecursive(arr, N, target);
    }
    stop = clock(); // Stop the timer
    SSR_time = (double)(stop - start) / CLOCKS_PER_SEC; // Calculate the run time (seconds)
    printf("Sequential Search Recursive: %f seconds\n", SSR_time);
    #endif
    return 0;
}