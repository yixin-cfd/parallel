cmake_minimum_required(VERSION 3.10)
project(MPI_Circuit VERSION 1.0)

# 设置C和C++编译器
set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpicxx)

# 查找MPI包
find_package(MPI REQUIRED)

# 如果找到MPI，输出信息
if(MPI_FOUND)
    message(STATUS "MPI found")
    message(STATUS "MPI include directories: ${MPI_INCLUDE_PATH}")
    message(STATUS "MPI libraries: ${MPI_LIBRARIES}")
    include_directories(${MPI_INCLUDE_PATH})
    link_directories(${MPI_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "MPI not found")
endif()

# 添加可执行文件
add_executable(MPI_Circuit v2.cpp)

# 链接MPI库
target_link_libraries(MPI_Circuit MPI::MPI_CXX)

# 设置运行所需的处理器核数
set(PROCESS_COUNT 10)

# 添加一个自定义目标来运行 MPI 程序
add_custom_target(run_mpi
    COMMAND ${MPIEXEC} -np ${PROCESS_COUNT} $<TARGET_FILE:MPI_Circuit>
    DEPENDS MPI_Circuit
    COMMENT "Running MPI_Circuit with ${PROCESS_COUNT} processor cores"
)
