cmake_minimum_required(VERSION 3.28)
project(fde_project1)


# 添加源文件
add_executable(
    fde_project1 
    main.c 
    BinarySearch_iterative.c BinarySearch_iterative.h
    BinarySearch_recursive.c BinarySearch_recursive.h
    SequentialSearch_iterative.c SequentialSearch_iterative.h
    SequentialSearch_recursive.c SequentialSearch_recursive.h
    )

# 标准
set(CMAKE_C_STANDARD 11)