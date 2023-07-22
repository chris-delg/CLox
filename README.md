# CLox
An interpreter for the Lox programming language implemented in c. This project is based off of the book [Crafting Interpreters](http://www.craftinginterpreters.com/contents.html) by [Bob Nystrom](https://github.com/munificent). This interpreter features a virtual machine that takes in bytecode instructions to execute the program.

# Build and Run
In order to build and run the interpreter, make sure you have CMake installed. Make sure that at minimum you have version 3.1 of CMake on your computer, then run the following commands

```shell
$ mkdir build
$ cd build
$ cmake .. && make
$ ./CLox
```
