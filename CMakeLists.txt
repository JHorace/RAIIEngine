cmake_minimum_required(VERSION 3.8)

set(HUNTER_ROOT "/cmake")
include("cmake/CPM.cmake")

project("RAIIEngine"
        LANGUAGES CXX)

CPMAddPackage("gh:gabime/spdlog@1.10.0")
CPMAddPackage(NAME SDL2
        VERSION 2.24.0
        GIT_TAG main
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git)


find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(SDL2 REQUIRED)

IF(${SDL2_FOUND})
    MESSAGE(STATUS "Found SDL")
ELSE(${SDL2_FOUND})
    MESSSAGE(STATUS "Could not find SDL")
ENDIF(${SDL2_FOUND})


add_subdirectory(engine)
add_subdirectory(samples)