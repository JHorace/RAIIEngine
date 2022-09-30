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
    
    Shader(const vk::Device & device, const uint32_t * spvBytes, uint32_t size, Stage stage);
    
    static std::vector<uint32_t> CompileSPV(const std::filesystem::path filePath, Stage stage);
  private:
    vk::raii::ShaderModule _shaderModule;
  };
}

#endif //RAIIENGINE_SHADER_HPP
