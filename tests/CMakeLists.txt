project(ForgeTests)

set(CMAKE_CXX_STANDARD 17)

CPMAddPackage(NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG release-1.12.1)

find_package(googletest)

enable_testing()

add_subdirectory(reflection)