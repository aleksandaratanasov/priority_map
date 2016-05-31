project(prioritymap_demo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-fPIC -std=gnu++14 ${CMAKE_CXX_FLAGS}") # Requires C++14

# Debug build
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O0")
# Release build
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os") # -Os optimizes for size (includes -O2 with a couple of flags disabled)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s") # -s strip binary

add_library(mode SHARED mode.cpp)
add_library(prioritymap SHARED prioritymap.cpp)
target_link_libraries(prioritymap mode)

set(SRC main.cpp)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC prioritymap)

