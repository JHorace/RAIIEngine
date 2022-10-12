add_executable(test_reflection src/main.cpp)

target_link_libraries(test_reflection PRIVATE reflection
        utils
        GTest::gtest_main)

set(shader_target
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/SimpleVertex.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/SimpleVertex.frag
        )

glsl_to_spirv(test_reflection shader_target)

include(GoogleTest)
gtest_discover_tests(test_reflection)