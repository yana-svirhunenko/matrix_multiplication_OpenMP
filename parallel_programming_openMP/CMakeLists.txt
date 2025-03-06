cmake_minimum_required(VERSION 3.28.3)
project(matmul)

find_package(OpenMP REQUIRED)

set(SOURCE_FILES
    main.cpp
    matrix_operations.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
