
project(reflection)


add_library(reflection STATIC include/shader_reflection.hpp src/shader_reflection.cpp header/conversions.hpp)

target_link_libraries(reflection PUBLIC render_descriptor)
target_link_libraries(reflection PRIVATE spirv-cross-core
        spirv-cross-glsl
        spirv-cross-reflect)

target_include_directories(reflection PUBLIC include)
