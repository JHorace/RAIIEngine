# Created 2022
# James Sumihiro and Bryan Johnson
# engine_vk_init

project(sample_engine_vk_init)

add_executable(sample_engine_vk_init
  src/main.cpp)

target_link_libraries(sample_engine_vk_init PRIVATE
  engine_vk)
