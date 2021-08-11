cmake_minimum_required(VERSION 3.14)

project(ucc VERSION 0.1)

enable_testing()

find_package(BISON)
find_package(FLEX)

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
    cc/ast/function.h
    cc/ast/function.cpp
    cc/ast/statement.h
    cc/ast/statement.cpp
    ${BISON_ucc_parser_OUTPUTS}
    ${FLEX_ucc_lexer_OUTPUTS}
)
target_include_directories(ucc PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(ucc PRIVATE ${CMAKE_SOURCE_DIR}/cc)

add_subdirectory(tests)