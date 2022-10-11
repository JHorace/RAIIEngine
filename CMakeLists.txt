# Created 2022
# James Sumihiro and Bryan Johnson
# RAIIEngine

cmake_minimum_required(VERSION 3.24)

###CPM functions
include("cmake/CPM.cmake")

set(CMAKE_UTILS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-utils")

###cmake utility functions
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake-utils/utils.cmake)


project("RAIIEngine" LANGUAGES CXX)

set(SHARED_ASSETS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets)


find_package(Vulkan REQUIRED)

CPMAddPackage("gh:gabime/spdlog@1.10.0")

CPMAddPackage(NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_INSTALL OFF")

### SPIRV-Cross and build options

set(SPIRV_CROSS_CLI OFF)
set(SPIRV_CROSS_ENABLE_TESTS OFF)
set(SPIRV_CROSS_ENABLE_GLSL ON)
set(SPIRV_CROSS_ENABLE_HLSL OFF)
set(SPIRV_CROSS_ENABLE_MSL OFF)
set(SPIRV_CROSS_ENABLE_CPP ON)
set(SPIRV_CROSS_ENABLE_C_API OFF)
set(SPIRV_CROSS_ENABLE_UTIL OFF)
set(SPIRV_CROSS_ENABLE_REFLECT ON)

CPMAddPackage(NAME SPIRV-Cross
        GITHUB_REPOSITORY KhronosGroup/SPIRV-Cross
        GIT_TAG sdk-1.3.224.1)

find_package(glfw REQUIRED)

if(!${glfw_FOUND})
    message("GLFW not found")
endif()

#add_subdirectory(${SPIRV-Cross_SOURCE_DIR})
add_subdirectory(utils)
add_subdirectory(render_descriptor)
add_subdirectory(reflection)
add_subdirectory(engine)
add_subdirectory(assets)
add_subdirectory(samples)
add_subdirectory(tests)


