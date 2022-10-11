//
// Created by jsumihiro on 10/9/22.
//

#include "shader_reflection.hpp"


ShaderDescriptor ReflectSPVShader(const std::vector<uint32_t> & spvBytes)
{
  ShaderDescriptor descriptor;
  spirv_cross::CompilerReflection comp(spvBytes);
  
  spv::ExecutionModel shaderStage = comp.get_execution_model();
  
  switch(shaderStage)
  {
    case spv::ExecutionModel::ExecutionModelVertex :
      descriptor._stage = ShaderStage::Vertex;
      return BuildVertexShaderDescriptor(descriptor, comp);
      break;
    default:
      break;
  }
  
  
  
  return ShaderDescriptor();
}

ShaderDescriptor ReflectSPVShader(const std::vector<char>& spvBytes)
{
    std::vector<uint32_t> spvWords;
    const uint32_t* wBegin = reinterpret_cast<const uint32_t*>(spvBytes.data());
    spvWords.assign(wBegin, wBegin + (spvBytes.size() / 4));
    
    return ReflectSPVShader(spvWords);
}

ShaderDescriptor BuildVertexShaderDescriptor(ShaderDescriptor& descriptor, const spirv_cross::CompilerReflection & comp)
{
  spirv_cross::ShaderResources resources = comp.get_shader_resources();
  
  PopulateVertexAttributeDescriptors(descriptor, comp, resources);
  
  for(const auto & inputAttribute : resources.stage_inputs)
  {
      descriptor._vertexDescriptor._attributes.push_back(BuildVertexAttributeDescriptor(comp, inputAttribute));
  }
  
  return ShaderDescriptor();
}

VertexAttributeDescriptor BuildVertexAttributeDescriptor(const spirv_cross::CompilerReflection& comp, const spirv_cross::Resource& inputAttribute)
{

  
  return VertexAttributeDescriptor{
    ._location = comp.get_decoration(inputAttribute.id, spv::DecorationLocation),
    ._binding = comp.get_decoration(inputAttribute.id, spv::DecorationBinding),
  };

}

void PopulateVertexAttributeDescriptors(ShaderDescriptor& descriptor, const spirv_cross::CompilerReflection& comp, const spirv_cross::ShaderResources& resources)
{

  for(const auto& inputAttribute : resources.stage_inputs)
  {
    descriptor._vertexDescriptor._attributes.push_back(BuildVertexAttributeDescriptor(comp, inputAttribute));
  }
}
