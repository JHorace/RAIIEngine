//
// Created by jsumihiro on 10/11/22.
//

#include "shader_reflection.hpp"
#include "utils.hpp"
#include "gtest/gtest.h"

namespace Forge
{
  namespace Tests
  {
    int main(void)
    {
      return 0;
    
    }
  
    TEST(ReflectionTests, ShaderStages) {
      std::vector<char> vertBytes = LoadBinaryFile("assets/shaders/spirv/SimpleVertex.vert.spv");
      std::vector<char> fragBytes = LoadBinaryFile("assets/shaders/spirv/SimpleVertex.frag.spv");
      ShaderDescriptor vertDescriptor = Reflection::ReflectSPVShader(vertBytes);
      ShaderDescriptor fragDescriptor = Reflection::ReflectSPVShader(fragBytes);
      EXPECT_EQ(vertDescriptor._stage, ShaderStage::Vertex);
      EXPECT_EQ(fragDescriptor._stage, ShaderStage::Fragment);
      
      
    }
  }
}


