# Created 2022
# James Sumihiro and Bryan Johnson
# RAIIEngine

cmake_minimum_required(VERSION 3.20)

set(CMAKE_VERBOSE_MAKEFILE ON)

include("cmake/CPM.cmake")

project("RAIIEngine" LANGUAGES CXX)

option(CPM_USE_LOCAL_PACKAGES "Attempt to use local packages first" ON)

CPMAddPackage("gh:gabime/spdlog@1.10.0")

CPMAddPackage(NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_WIN32 ON"
        "GLFW_INSTALL OFF")

#CPMAddPackage("gh:KhronosGroup/Vulkan-Hpp@1.3.227")
#CPMAddPackage("gh:KhronosGroup/Vulkan-Loader@1.3.227")


find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw REQUIRED FATAL_ERROR)

if(!${glfw_FOUND})
    message("GLFW not found")
endif()


add_subdirectory(engine)
add_subdirectory(samples)