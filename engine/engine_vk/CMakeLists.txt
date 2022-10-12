# Created 2022
# James Sumihiro and Bryan Johnson
# engine_vk

project(engine_vk)

add_library(engine_vk STATIC
  src/engine_vk.cpp header/engine_vk.hpp
  src/engine_vk_factory.cpp include/engine_vk_factory.hpp
  src/logical_device.cpp header/logical_device.hpp
  src/queue_manager.cpp header/queue_manager.hpp
  src/debug.cpp header/debug.hpp
  src/renderer.cpp header/renderer.hpp
  src/swapchain.cpp header/swapchain.hpp
  src/surface.cpp header/surface.hpp
  src/device_manager.cpp header/device_manager.hpp
  header/device_manager.hpp header/engine_defaults.hpp
  src/command_dispatch.cpp header/command_dispatch.hpp
  src/pipeline.cpp header/pipeline.hpp
  src/shader.cpp header/shader.hpp
  header/conversions.hpp)


target_compile_features(engine_vk PRIVATE
  cxx_std_20
  cxx_constexpr
  cxx_aggregate_default_initializers)

target_link_libraries(engine_vk PUBLIC
  i_engine
  glfw
  )

target_link_libraries(engine_vk PRIVATE
  Vulkan::Vulkan
  spdlog::spdlog
  render_descriptor
  utils
  )

target_include_directories(engine_vk PUBLIC include/)
target_include_directories(engine_vk PRIVATE header/)
