#find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)
#
#set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/assets/shaders)
#
#add_custom_command(COMMAND
#        ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
#        OUTPUT ${SHADER_BINARY_DIR})
#
#file(GLOB SHADERS
#        ${SHADER_SOURCE_DIR}/*.vert
#        ${SHADER_SOURCE_DIR}/*.frag)
#
#foreach(source IN LISTS SHADERS)
#
#    get_filename_component(FILENAME ${source} NAME)
#    add_custom_command(
#            COMMAND
#            ${glslc_executable} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
#            ${source}
#            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
#            DEPENDS ${source} ${SHADER_BINARY_DIR}
#            COMMENT "Compiling ${FILENAME}"
#    )
#    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
#endforeach()
#
#
#add_custom_target(shader_bins ALL DEPENDS ${SPV_SHADERS})


