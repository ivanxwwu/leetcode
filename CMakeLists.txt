cmake_minimum_required(VERSION 3.7)
project(leetcode)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS  ${CMAKE_C_FLAGS} -g)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fpermissive)
macro(add_example_target EXAMPLE_TARGET)
    add_executable("example_${EXAMPLE_TARGET}" "example_${EXAMPLE_TARGET}.c")
    target_link_libraries("example_${EXAMPLE_TARGET}" pthread)
    target_link_libraries("example_${EXAMPLE_TARGET}" libhiredis.a)
    target_link_libraries("example_${EXAMPLE_TARGET}" libev.a)
endmacro(add_example_target)

add_example_target(1_twosum)

#add_executable("main" "main.cpp")