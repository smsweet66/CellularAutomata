cmake_minimum_required(VERSION 3.15)
project(CellularAutomata)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)
add_subdirectory(lib)
FILE(REMOVE_RECURSE ${PROJECT_BINARY_DIR}/src/res)
FILE(COPY res DESTINATION ${PROJECT_BINARY_DIR}/src)