project(sample_engine_vk_init)

add_executable(sample_engine_vk_init src/main.cpp)

target_include_directories(sample_engine_vk_init PRIVATE SDL2::SDL2Main)

target_link_libraries(sample_engine_vk_init
        engine_vk
        SDL2::SDL2)