// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_SHADER_HPP
#define RAIIENGINE_SHADER_HPP

#include "p_includes.hpp"
#include <filesystem>

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
    
    Shader(const vk::raii::Device & device, const std::vector<uint32_t> & spvBytes, Stage stage);
    
    static std::vector<uint32_t> CompileSPV(const std::filesystem::path & filePath, Stage stage);
  private:
    vk::ShaderModuleCreateInfo CIBuilder(const std::vector<uint32_t> & spvBytes);
    
    vk::raii::ShaderModule _shaderModule;
  };
}

#endif //RAIIENGINE_SHADER_HPP
