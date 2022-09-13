# Created 2022
# James Sumihiro and Bryan Johnson
# window

project(window_handler)

add_library(window_handler STATIC
  window_handler.cpp window_handler.hpp)

target_compile_features(window_handler PRIVATE
        cxx_std_20)

target_link_libraries(window_handler PUBLIC
  glfw)
