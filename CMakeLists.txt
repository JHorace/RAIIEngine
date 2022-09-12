# Created 2022
# James Sumihiro and Bryan Johnson
# RAIIEngine

cmake_minimum_required(VERSION 3.20)

include("cmake/CPM.cmake")

project("RAIIEngine" LANGUAGES CXX)

CPMAddPackage("gh:gabime/spdlog@1.10.0")

CPMAddPackage(NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BULID_DOCS OFF"
        "GLFW_BUILD_X11 ON")


find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw REQUIRED FATAL_ERROR)

add_subdirectory(engine)
add_subdirectory(samples)