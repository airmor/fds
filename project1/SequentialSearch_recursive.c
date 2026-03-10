#include "SequentialSearch_recursive.h"
#include <stdio.h>

int SequentialSearchRecursive(int arr[], int len, int x) {
    if(len==0) {
        return -1;
    }
    if(arr[0] == x) {
        return 0;
    }
    else{
        int tmp = SequentialSearchRecursive(arr+1, len-1, x);
        if(tmp == -1) {
            return -1;
        }
        else {
            return tmp + 1;
        }
    }
}