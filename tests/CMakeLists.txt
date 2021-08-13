cmake_minimum_required(VERSION 3.14)

macro(cc_success_test name)
    add_test(
        NAME cc_test_${name}
        COMMAND $<TARGET_FILE:ucc> ${CMAKE_CURRENT_SOURCE_DIR}/cc/${name}.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

macro(cc_ir_test name)
    add_test(
        NAME cc_ir_test_${name}
        COMMAND sh -c "$<TARGET_FILE:ucc> ${CMAKE_CURRENT_SOURCE_DIR}/cc/${name}.c | diff - ${CMAKE_CURRENT_SOURCE_DIR}/cc/${name}.ir"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

# C Compiler Tests
cc_success_test("simple_functions")
cc_ir_test("simple_functions")