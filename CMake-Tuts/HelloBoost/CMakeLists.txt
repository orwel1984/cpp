cmake_minimum_required(VERSION 3.27)
project(HelloBoost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost library within the project's external directoy
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/boost")

# set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/libs")

# set(BOOST_INCLUDE_LIBRARIES filesystem regex program_options date_time)

#add_subdirectory(external/boost EXCLUDE_FROM_ALL)

FIND_PACKAGE(Boost 1.84.0 REQUIRED )

# FIND_PACKAGE(Boost "1.84.0" COMPONENTS program_options date_time filesystem  REQUIRED)

# Specify sources explicitly
set(SOURCES
   ${SOURCES}
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main_headerOnly.cpp
)

add_executable(HelloBoost ${SOURCES})

message(STATUS "BOOST_ROOT: ${BOOST_ROOT}")
message(STATUS "Boost Include Dir: " ${Boost_INCLUDE_DIR})
message(STATUS "Boost Library Dir: " ${Boost_LIBRARY_DIR})

# Set Boost's include's folder and link libraries to executable target
#TARGET_LINK_DIRECTORIES(HelloBoost PUBLIC ${Boost_INCLUDE_DIR}) 
#TARGET_LINK_LIBRARIES(HelloBoost ${Boost_LIBRARY_DIR})
TARGET_LINK_LIBRARIES(HelloBoost PUBLIC Boost::headers Boost::boost )
# TARGET_LINK_LIBRARIES(HelloBoost Boost::program_options Boost::date_time Boost::filesystem)
