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
  
  Shader::Shader(const vk::raii::Device & device,
                 const std::vector<uint32_t> & spvBytes,
                 Stage stage)
    :
    _shaderModule{device, CIBuilder(spvBytes)}
  {
  
  }
  
  vk::ShaderModuleCreateInfo Shader::CIBuilder(const std::vector<uint32_t> & spvBytes)
  {
    return vk::ShaderModuleCreateInfo{
      .codeSize = spvBytes.size(),
      .pCode = spvBytes.data()
    };
  }
  
  // TODO: Move shader compilation out of Shader and/or out of Engine entirely.
  
  // Naively dumps a file into a string.
  std::string DumpFile(const std::filesystem::path & relative_path)
  {
    std::ifstream file_stream(std::filesystem::absolute(relative_path));
    
    if (!file_stream.good())
      std::cout << std::filesystem::absolute(relative_path).string() << ": " << strerror(errno) << "\n";
    
    return (std::stringstream() << file_stream.rdbuf()).str();
  }
  
  /*
  std::vector<uint32_t> Shader::CompileSPV(const std::filesystem::path & filePath,
                                           Shader::Stage stage)
  {
    static std::unordered_map<Shader::Stage, shaderc_shader_kind> stageMap{
      {Shader::Stage::vertex,   shaderc_shader_kind::shaderc_vertex_shader},
      {Shader::Stage::fragment, shaderc_shader_kind::shaderc_fragment_shader}
    };
    
    auto src = DumpFile(filePath);
    shaderc::Compiler compiler;
    auto vertResult = compiler.CompileGlslToSpv(src, stageMap[stage], filePath.filename().generic_string().c_str());
    
    // TODO print error/warning messages.
    
    return std::vector<uint32_t>{vertResult.begin(), vertResult.end()};
  }
   */
}
