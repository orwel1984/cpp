project(HelloBenchmark)
cmake_minimum_required(VERSION 3.8)

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify sources explicitly
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(HelloBenchmark ${SOURCES})

# Benchmark Library
add_subdirectory(external/benchmark)
target_link_libraries(HelloBenchmark benchmark::benchmark)
