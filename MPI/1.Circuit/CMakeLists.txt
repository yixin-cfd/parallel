cmake_minimum_required(VERSION 3.10)
project(MPI_Circuit VERSION 1.0 LANGUAGES CXX C)
 
include_directories(/usr/lib/x86_64-linux-gnu/openmpi/include)


# 设置C和C++编译器为MPI编译器包装器
set(MPI_C_COMPILER /usr/bin/mpicc)
set(MPI_CXX_COMPILER /usr/bin/mpicxx)

set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpicxx)


# 查找MPI库
find_package(MPI REQUIRED)
 
# 如果找到MPI，输出信息
if(MPI_FOUND)
    message(STATUS "MPI found")
    message(STATUS "MPI C compiler: ${MPI_C_COMPILER}")
    message(STATUS "MPI CXX compiler: ${MPI_CXX_COMPILER}")
    message(STATUS "MPI include directories: ${MPI_INCLUDE_DIRS}")
    message(STATUS "MPI libraries: ${MPI_LIBRARIES}")
    message(STATUS "MPI library directories: ${MPI_LIBRARY_DIRS}")
else()
    message(FATAL_ERROR "MPI not found")
endif()
 
# 包含MPI的头文件目录
include_directories(${MPI_INCLUDE_DIRS})
 
# 添加可执行文件
add_executable(sta_v1 src/sta_v1.cpp)
add_executable(sta_v2 src/sta_v2.cpp)
add_executable(test src/test.cpp)
 
# 链接MPI库到目标可执行文件
target_link_libraries(sta_v1 ${MPI_LIBRARIES})
target_link_libraries(sta_v2 ${MPI_LIBRARIES})
target_link_libraries(test ${MPI_LIBRARIES})
 
# 将可执行文件放在 bin 目录下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)