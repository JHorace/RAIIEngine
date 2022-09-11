# Created 2022
# James Sumihiro and Bryan Johnson
# RAIIEngine

cmake_minimum_required(VERSION 3.20)

include("cmake/CPM.cmake")

project("RAIIEngine" LANGUAGES CXX)

CPMAddPackage("gh:gabime/spdlog@1.10.0")

CPMAddPackage(NAME glfw
  VERSION 3.3.8
  GIT_TAG master
  GIT_REPOSITORY https://github.com/glfw/glfw.git)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw REQUIRED)

if(glfw)
  message(GLFW found)
else()
  message(GLFW not found)
endif()

add_subdirectory(engine)
add_subdirectory(samples)