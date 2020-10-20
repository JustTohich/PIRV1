cmake_minimum_required(VERSION 2.8.9)
project (lab1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fopenmp")

set(COMMON_DEPS common.h common.c)

add_executable(main main.c ${COMMON_DEPS})

add_executable(test-multiply test-multiply.c ${COMMON_DEPS})
add_executable(test-output test-output.c ${COMMON_DEPS})
add_test(test-multiply test-multiply)
add_test(test-output test-output)

enable_testing()
