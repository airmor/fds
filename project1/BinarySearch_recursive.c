#include "BinarySearch_recursive.h"
#include <stdio.h>

int BinarySearchRecursive(int arr[], int len, int x){
    if(len == 0) return -1;
    if(arr[len/2] == x) return len/2;
    if(arr[len/2] > x){
        int tmp=BinarySearchRecursive(arr, len/2, x);
        if(tmp==-1) return -1;
        else return tmp;
    }
    else{
        int tmp=BinarySearchRecursive(arr+len/2+1, len-len/2-1, x);
        if(tmp==-1) return -1;
        else return tmp+len/2+1;
    }
}