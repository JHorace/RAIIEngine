project(render_descriptions)


add_library(render_descriptions INTERFACE include/shader_description.hpp include/formats.hpp)

target_include_directories(render_descriptions INTERFACE include/)
