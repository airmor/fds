#include "BinarySearch_iterative.h"
#include <stdio.h>

int BinarySearchIterative(int arr[], int len, int x){
    int left=0, right=len-1, mid;
    while(left<right){
        mid=(left+right)/2;
        if(arr[mid]==x)
            return mid;
        else if(arr[mid]<x)
            left=mid+1;
        else
            right=mid-1;
    }
    if(arr[left]==x){
    return left;
    }
    else{
    return -1;
    }
}