// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_SHADER_HPP
#define RAIIENGINE_SHADER_HPP

#include "p_includes.hpp"
#include <filesystem>
#include "shader_descriptor.hpp"

namespace Forge
{
  class Shader
  {
  public:
    enum class Stage
    {
      vertex,
      fragment
    };
    
    Shader(const vk::raii::Device & device, const std::vector<char> & spvBytes, Stage stage);
    Shader(const ShaderDescriptor& desc);
    
    vk::PipelineShaderStageCreateInfo CreateCI();
  private:
    vk::ShaderModuleCreateInfo CIBuilder(const std::vector<char> & spvBytes);
    
    vk::raii::ShaderModule _shaderModule;
    vk::ShaderStageFlagBits _stage;
  };
}

#endif //RAIIENGINE_SHADER_HPP
