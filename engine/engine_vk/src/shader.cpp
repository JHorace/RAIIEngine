// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "shader.hpp"
//#include "glslang/SPIRV/GlslangToSpv.h"
//#include "shaderc/shaderc.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace Forge
{
  const std::unordered_map<Shader::Stage, vk::ShaderStageFlagBits> stageMap{
    {Shader::Stage::vertex,   vk::ShaderStageFlagBits::eVertex},
    {Shader::Stage::fragment, vk::ShaderStageFlagBits::eFragment}
  };
  
  Shader::Shader(const vk::raii::Device & device,
                 const std::vector<char> & spvBytes,
                 Stage stage)
    :
    _shaderModule{device, CIBuilder(spvBytes)},
    _stage(stageMap.at(stage))
  {}
  
  vk::ShaderModuleCreateInfo Shader::CIBuilder(const std::vector<char> & spvBytes)
  {
    auto code = reinterpret_cast<const uint32_t *>(spvBytes.data());
    
    return vk::ShaderModuleCreateInfo{
      .codeSize = spvBytes.size(),
      .pCode = code
    };
  }
  
  vk::PipelineShaderStageCreateInfo Shader::CreateCI()
  {
    return vk::PipelineShaderStageCreateInfo{
      .stage = _stage,
      .module = *_shaderModule,
      .pName = "main"
    };
  }
}
