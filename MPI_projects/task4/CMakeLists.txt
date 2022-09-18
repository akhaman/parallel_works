cmake_minimum_required(VERSION 3.21)
project(task4)

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/Cellar/open-mpi/4.1.3/include)
set(CMAKE_C_COMPILER "/usr/local/Cellar/open-mpi/4.1.3/bin/mpicc")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/open-mpi/4.1.3/bin/mpic++")
add_executable(task4 main.cpp)
