# Created 2022
# James Sumihiro and Bryan Johnson
# geometry

add_library(geometry INTERFACE)

target_compile_features(geometry INTERFACE
        cxx_std_20
)

target_link_libraries(geometry INTERFACE)

target_include_directories(geometry INTERFACE include/)
