cmake_minimum_required(VERSION 3.21)
project(OpenMP)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang\$")
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include")
    set(OpenMP_CXX_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.dylib")
endif ()

find_package(OpenMP REQUIRED)

add_executable(OpenMP main.cpp)
target_link_libraries(OpenMP PRIVATE OpenMP::OpenMP_CXX)
