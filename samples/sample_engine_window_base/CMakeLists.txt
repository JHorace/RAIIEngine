# Created 2022
# James Sumihiro and Bryan Johnson
# sample_engine_window_base

project(sample_engine_window_base)

add_executable(sample_engine_window_base
  src/main.cpp)

target_link_libraries(sample_engine_window_base PRIVATE
  engine_vk
  window_handler)
