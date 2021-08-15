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

### Build compiler
```
$ mkdir build && cd build && cmake ..
$ cmake --build .
```

### Run compiler and generate executable

```
$ ./ucc ../examples/simple_program.c > simple_program.ll
$ llvm-as-12 simple_program.ll -o simple_program.bc
$ llc-12 simple_program.bc -o simple_program.S
$ clang simple_program.S -o simple_program
$ ./simple_program ; echo $?

```


```
$ ./ucc ../tests/cc/function_call.c > function_call.ll
$ llvm-as-12 function_call.ll -o function_call.bc
$ llc-12 function_call.bc -o function_call.S
$ clang function_call.S -o function_call
$ ./function_call ; echo $?

```

see also https://github.com/ulmer-a/ucc/issues/4
