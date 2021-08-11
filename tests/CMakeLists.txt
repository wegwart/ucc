cmake_minimum_required(VERSION 3.14)

macro(cc_success_test name)
    add_test(
        NAME cc_test_${name}
        COMMAND $<TARGET_FILE:ucc> ${CMAKE_CURRENT_SOURCE_DIR}/cc/${name}.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

# C Compiler Tests
cc_success_test("simple_functions")