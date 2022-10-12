###cmake utility functions###

function(glsl_to_spirv TARGET SOURCE_SHADERS)
    
    find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

    set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/assets/shaders/spirv)

    add_custom_command(COMMAND
            ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
            OUTPUT ${SHADER_BINARY_DIR})

    set(SPV_SHADERS_TARGET_NAME ${TARGET}_SPV_SHADERS)
    set(SPV_SHADERS "")

    foreach(source IN LISTS ${SOURCE_SHADERS})
        get_filename_component(FILENAME ${source} NAME)
        add_custom_command(
                COMMAND
                ${glslc_executable} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
                ${source}
                OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
                DEPENDS ${source} ${SHADER_BINARY_DIR}
                COMMENT "Compiling ${FILENAME}"
        )

        list(APPEND SPV_SHADERS "${SHADER_BINARY_DIR}/${FILENAME}.spv")
        message("Building shader: " ${source})
    endforeach()
    add_custom_target(${SPV_SHADERS_TARGET_NAME} ALL DEPENDS ${SPV_SHADERS})
    add_dependencies(${TARGET} ${SPV_SHADERS_TARGET_NAME})
    message("Target name:  ${SPV_SHADERS_TARGET_NAME}")
    message("Shaders:  ${SPV_SHADERS}")
endfunction()

function(generate_config_file TARGET)

set(APP_NAME "${PROJECT_NAME}" PARENT_SCOPE)
set(APP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} PARENT_SCOPE)
set(APP_VERSION_MINOR ${PROJECT_VERSION_MINOR} PARENT_SCOPE)

endfunction()