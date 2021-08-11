## UCC Ulmer C Compiler

This is an experimental C compiler written in C++ using bison/flex and LLVM. It's used by me to learn
about compiler construction.

### Project status
Currently, I'm working on the parser to build an abstract syntax tree (AST). At the moment, It can
recognize function declarations and definitions as well as simple expressions.

### Build and run
Use the standard CMake build procedure. The following prerequisites have to be installed
on your machine before you can build:
* bison
* flex
* llvm-dev
