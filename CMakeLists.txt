# Created 2022
# James Sumihiro and Bryan Johnson
# RAIIEngine

cmake_minimum_required(VERSION 3.24)

set(SHADERC_SKIP_TESTS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

include("cmake/CPM.cmake")

project("RAIIEngine" LANGUAGES CXX)

find_package(Vulkan REQUIRED)

#execute_process("")

#option(CPM_USE_LOCAL_PACKAGES "Attempt to use local packages first" ON)

CPMAddPackage("gh:gabime/spdlog@1.10.0")

CPMAddPackage(NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_INSTALL OFF")

#CPMAddPackage(
#  NAME spirvheaders
#  GITHUB_REPOSITORY KhronosGroup/SPIRV-Headers
#  GIT_TAG 1.5.3.reservations1
#)

#CPMAddPackage(
#  NAME spirvtools
#  GITHUB_REPOSITORY KhronosGroup/SPIRV-Tools
#  GIT_TAG v2022.2
#)

#CPMAddPackage(NAME glslang
#  GITHUB_REPOSITORY KhronosGroup/glslang
#  GIT_TAG 11.11.0
#  )

CPMAddPackage(NAME shaderc
  GITHUB_REPOSITORY google/shaderc
  GIT_TAG v2022.2
  DOWNLOAD_ONLY YES
  )

find_package(glfw REQUIRED)
find_package(shaderc REQUIRED)

if(!${glfw_FOUND})
    message("GLFW not found")
endif()

add_subdirectory(engine)
add_subdirectory(samples)