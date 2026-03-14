#include <stdio.h>
#include <stdlib.h>
int main() {
    // 读取输入的整数 n 和 h
    int n=0,h=0;
    scanf("%d %d",&n,&h);
    // 动态分配一个大小为 n 的整数数组
    int *arr = (int*) malloc(n*sizeof(int));
    // 循环读取 n 个整数并存储到数组中
    for(int i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    // 初始化 Position 和 NUM 用于存储结果
    int Position=0,NUM=0;
    // 循环遍历数组，计算符合条件的最长连续子数组
    for(int i=0;i<n;i++){
        int CN=1;
        // 检查当前元素与前面的元素是否满足条件
        while(i-CN>=0 && arr[i]-h<=arr[i-CN]){
            CN++;
        }
        // 更新 NUM 和 Position 如果找到更长的符合条件的子数组
        if(CN>NUM){
            NUM=CN;
            Position=arr[i]-h;
        }
    }
    // 输出结果
    printf("%d %d\n",Position,NUM);
    // 释放动态分配的内存并返回 0
    return 0;
}