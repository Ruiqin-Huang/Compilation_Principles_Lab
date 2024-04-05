#!/bin/bash

# 编译C++代码
g++ -std=c++11 compilerlab1.cpp -o compilerlab1

# 如果编译成功，则执行程序
if [ $? -eq 0 ]; then
   ./compilerlab1 ./test_input_2.txt
fi