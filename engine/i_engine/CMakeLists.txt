# Created 2022
# James Sumihiro and Bryan Johnson
# i_engine

add_library(i_engine INTERFACE)

target_compile_features(i_engine INTERFACE
        cxx_std_20
)

target_link_libraries(i_engine INTERFACE
        window_handler
        render_descriptions)

target_include_directories(i_engine INTERFACE include/)
