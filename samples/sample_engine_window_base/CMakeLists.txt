# Created 2022
# James Sumihiro and Bryan Johnson
# sample_engine_window_base

project(sample_engine_window_base
        VERSION 0.1)



add_executable(sample_engine_window_base
  src/main.cpp)


target_link_libraries(sample_engine_window_base PRIVATE
  engine_vk
  window_handler)

glsl_to_spirv(sample_engine_window_base ${SHARED_ASSETS_PATH}/shaders/simple.vert)

generate_config_file(sample_engine_window_base)

configure_file("${CMAKE_UTILS_PATH}/app_config.hpp.in"
        "${PROJECT_BINARY_DIR}/include/app_config.hpp")

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
