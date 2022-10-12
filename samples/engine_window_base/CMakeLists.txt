# Created 2022
# James Sumihiro and Bryan Johnson
# engine_window_base

project(sample_engine_window_base
        VERSION 0.1)



add_executable(sample_engine_window_base
  src/main.cpp)


target_link_libraries(sample_engine_window_base PRIVATE
  engine_vk
  window_handler)

set(shader_target
  ${SHARED_ASSETS_PATH}/shaders/simple.vert
  ${SHARED_ASSETS_PATH}/shaders/simple.frag
  )

glsl_to_spirv(engine_vk shader_target)

generate_config_file(sample_engine_window_base)

configure_file("${CMAKE_UTILS_PATH}/app_config.hpp.in"
        "${PROJECT_BINARY_DIR}/include/app_config.hpp")

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
