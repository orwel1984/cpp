project(HelloBoost)
cmake_minimum_required(VERSION 3.8)

# Find Boost library within the project's external directoy
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/boost_1_82_0")
# set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/lib")
find_package(Boost 1.82 COMPONENTS program_options date_time filesystem  REQUIRED)

# Specify sources explicitly
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# set(HEADERS
#    ${HEADERS}
#    ${CMAKE_CURRENT_SOURCE_DIR}/file1.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/file2.hpp
#    PARENT_SCOPE
# )

add_executable(HelloBoost ${SOURCES})

message(STATUS "Boost Include Dir: " ${Boost_INCLUDE_DIR})

# Set Boost's include's folder and link libraries to executable target
target_include_directories(HelloBoost PUBLIC ${Boost_INCLUDE_DIR}) 
target_link_libraries(HelloBoost ${Boost_LIBRARY_DIR})
target_link_libraries(HelloBoost Boost::program_options Boost::date_time Boost::filesystem)
