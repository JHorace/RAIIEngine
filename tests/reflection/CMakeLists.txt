add_executable(test_reflection src/main.cpp)

target_link_libraries(test_reflection PRIVATE reflection
        utils)

glsl_to_spirv(test_reflection ${SHARED_ASSETS_PATH}/shaders/simple.vert)