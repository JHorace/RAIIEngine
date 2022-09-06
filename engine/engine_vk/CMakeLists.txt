project(engine_vk)

add_library(engine_vk STATIC src/engine_vk.cpp include/engine_vk.hpp src/engine_vk_factory.cpp include/engine_vk_factory.hpp src/device_wrapper.cpp include/device_wrapper.hpp src/queue_manager.cpp include/queue_manager.hpp include/p_includes.hpp include/debug.hpp src/debug.cpp src/renderer.cpp src/swapchain.cpp include/renderer.hpp include/swapchain.hpp "src/surface.cpp")

target_compile_features(engine_vk PRIVATE
        cxx_std_20
        cxx_aggregate_default_initializers)

target_link_libraries(engine_vk PUBLIC
        i_engine)

target_link_libraries(engine_vk PRIVATE
        Vulkan::Vulkan
        spdlog::spdlog)

target_include_directories(engine_vk PUBLIC include/)
