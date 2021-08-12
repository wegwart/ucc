cmake_minimum_required(VERSION 3.14)

project(ucc VERSION 0.1)

enable_testing()

# find bison/flex for lexing and parsing
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
message(STATUS "Found flex ${FLEX_VERSION}")
message(STATUS "Found bison ${BISON_VERSION}")

# find LLVM for code generation
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
llvm_map_components_to_libnames(llvm_libs support core irreader)

bison_target(ucc_parser
    cc/grammar.y
    ${CMAKE_BINARY_DIR}/ucc_parser.cpp
    DEFINES_FILE ${CMAKE_BINARY_DIR}/cc_lexer.h
)

flex_target(ucc_lexer
    cc/tokens.l
    ${CMAKE_BINARY_DIR}/cc_lexer.cpp
)

add_flex_bison_dependency(ucc_lexer ucc_parser)

add_executable(ucc
    cc/main.cpp
    cc/parser.cpp
    cc/ast/object.h
    cc/ast/object.cpp
    cc/ast/function.h
    cc/ast/function.cpp
    cc/ast/statement.h
    cc/ast/statement.cpp
    cc/codegen/generator.h
    cc/codegen/generator.cpp
    ${BISON_ucc_parser_OUTPUTS}
    ${FLEX_ucc_lexer_OUTPUTS}
)
target_link_libraries(ucc ${llvm_libs})
target_include_directories(ucc PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(ucc PRIVATE ${CMAKE_SOURCE_DIR}/cc)

add_subdirectory(tests)