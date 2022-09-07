# Created 2022
# James Sumihiro and Bryan Johnson
# engine_vk

project(engine_vk)

add_library(engine_vk STATIC 
  src/engine_vk.cpp
  src/engine_vk_factory.cpp
  src/device.cpp
  src/queue_manager.cpp 
  src/debug.cpp 
  src/renderer.cpp
  src/swapchain.cpp 
  src/surface.cpp
)

target_compile_features(engine_vk PRIVATE
        cxx_std_20
        cxx_aggregate_default_initializers
)

target_link_libraries(engine_vk PUBLIC
        i_engine
)

target_link_libraries(engine_vk PRIVATE
        Vulkan::Vulkan
        spdlog::spdlog
)

target_include_directories(engine_vk PUBLIC include/)
target_include_directories(engine_vk PRIVATE header/)
