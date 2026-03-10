cmake_minimum_required(VERSION 3.28)
project(fds_project1)


# 添加源文件
add_executable(
    fds_project1 
    main.c 
    BinarySearch_iterative.c BinarySearch_iterative.h
    BinarySearch_recursive.c BinarySearch_recursive.h
    SequentialSearch_iterative.c SequentialSearch_iterative.h
    SequentialSearch_recursive.c SequentialSearch_recursive.h
    )

# 设置不同算法的循环次数K和整数数量N
set(K_BSI 1000000) # Binary Search Iterative
set(K_BSR 1000000) # Binary Search Recursive
set(K_SSI 1000000) # Sequential Search Iterative
set(K_SSR 1000000) # Sequential Search Recursive
set(N 10000) # Integer Quantity

# 设置要运行的测试
set(BSI 1)
set(BSR 1)
set(SSI 1)
set(SSR 1)

# 设置宏定义
target_compile_definitions(fds_project1 PRIVATE 
    K_BSI=${K_BSI}
    K_BSR=${K_BSR}
    K_SSI=${K_SSI}
    K_SSR=${K_SSR}
    N=${N}
    BSI=${BSI}
    BSR=${BSR}
    SSI=${SSI}
    SSR=${SSR}
)