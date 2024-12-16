cmake_minimum_required(VERSION 3.20)
project(HelloVulkan)

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify sources explicitly
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/VulkanApplication.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(HelloVulkan ${SOURCES})

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED FATAL_ERROR)
find_package(glm REQUIRED FATAL_ERROR)

# Link Libraries to .exe
target_link_libraries(HelloVulkan glfw)
target_link_libraries(HelloVulkan glm::glm)

message(STATUS "GLFW3 dir ${glfw3_DIR}")
message(STATUS "GLM dir ${glm_DIR}")
message(STATUS "VULKAN dir${vulkan_DIR}")

if (VULKAN_FOUND)
    message(STATUS "Found Vulkan. Including and linking...")
    target_link_libraries(HelloVulkan Vulkan::Vulkan)
endif(VULKAN_FOUND)
