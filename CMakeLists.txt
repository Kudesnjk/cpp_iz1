cmake_minimum_required(VERSION 3.12)
project(homework1)
set(CMAKE_C_STANDARD 99)

add_library(functions STATIC libs/functions.h libs/functions.c)

set(SOURCE_FILES main.c)
add_executable(homework1 ${SOURCE_FILES})
target_link_libraries(homework1 functions)

add_executable(TEST unit_tests.c)
target_link_libraries(TEST functions)

enable_testing()
add_test(UnitTests TEST)
