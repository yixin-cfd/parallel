cmake_minimum_required(VERSION 3.8)
project(hello_omp)

add_executable(hello_omp main.cpp)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(hello_omp PUBLIC OpenMP::OpenMP_CXX)
    target_compile_options(hello_omp PUBLIC -O2 -fopenmp)
endif()
