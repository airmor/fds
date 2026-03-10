#include "SequentialSearch_iterative.h"
#include <stdio.h>

int SequentialSearch_iterative(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Return the index of the target element
        }
    }
    return -1; // Return -1 if the target element is not found
}