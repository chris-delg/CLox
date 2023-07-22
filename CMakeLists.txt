
cmake_minimum_required(VERSION 3.1)

project(CLox)

add_executable(CLox 
    src/chunk.c 
    src/debug.c 
    src/main.c 
    src/memory.c 
    src/value.c
    src/vm.c
)