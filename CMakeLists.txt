cmake_minimum_required(VERSION 3.14)

project(ucc VERSION 0.1)

find_package(BISON)
find_package(FLEX)

bison_target(ucc_parser
    ucc/grammar.y
    ${CMAKE_BINARY_DIR}/ucc_parser.c
    DEFINES_FILE ${CMAKE_BINARY_DIR}/ucc_lexer.h
)

flex_target(ucc_lexer
    ucc/tokens.l
    ${CMAKE_BINARY_DIR}/ucc_lexer.c
)

add_flex_bison_dependency(ucc_lexer ucc_parser)

add_executable(ucc
    ucc/main.cpp
    ${BISON_ucc_parser_OUTPUTS}
    ${FLEX_ucc_lexer_OUTPUTS}
)
target_include_directories(ucc PRIVATE ${CMAKE_BINARY_DIR})

