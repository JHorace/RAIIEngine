# Created 2022
# James Sumihiro and Bryan Johnson
# window_handler

project(window_handler)

add_library(window_handler STATIC
  window_handler.cpp window_handler.hpp)

target_compile_features(window_handler PRIVATE
        cxx_std_20)

target_link_libraries(window_handler PRIVATE
  glfw)

target_include_directories(window_handler PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/)
