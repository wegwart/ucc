## UCC Ulmer C Compiler

This is an experimental C compiler written in C++ using bison/flex and LLVM. It's used by me to learn
about compiler construction. Currently it can generate LLVM IR from simple C functions and print it
out on the terminal.

### Building
Use the standard CMake build procedure. The following prerequisites have to be installed
on your machine before you can build:
* CMake
* build-essential
* bison
* flex
* llvm-12-dev