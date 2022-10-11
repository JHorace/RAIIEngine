//
// Created by jsumihiro on 10/11/22.
//

#include "shader_reflection.hpp"
#include "utils.hpp"

int main(void)
{
  std::vector<char> spvBytes = LoadBinaryFile("assets/shaders/spirv/simple.vert.spv");
  ReflectSPVShader(spvBytes);
}