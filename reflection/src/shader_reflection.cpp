//
// Created by jsumihiro on 10/9/22.
//

#include "shader_reflection.hpp"
#include "conversions.hpp"


namespace Forge::Reflection
{
  ShaderDescriptor ReflectSPVShader(const std::vector<uint32_t> & spvBytes)
  {
    spirv_cross::CompilerReflection comp(spvBytes);
    spv::ExecutionModel shaderStage = comp.get_execution_model();
  
    switch(shaderStage)
    {
      case spv::ExecutionModelVertex :
        return BuildVertexShaderDescriptor(comp);
      case spv::ExecutionModelFragment :
        return BuildFragmentShaderDescriptor(comp);
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
    
    return Forge::Reflection::ReflectSPVShader(spvWords);
  }
  
  ShaderDescriptor BuildVertexShaderDescriptor(const spirv_cross::CompilerReflection & comp)
  {
    ShaderDescriptor descriptor{
      ._stage = ShaderStage::Vertex,
    };
    
    spirv_cross::ShaderResources resources = comp.get_shader_resources();
    
    PopulateVertexAttributeDescriptors(descriptor, comp, resources);
    
    for(const auto & inputAttribute : resources.stage_inputs)
    {
      descriptor._vertexDescriptor._attributes.push_back(BuildVertexAttributeDescriptor(comp, inputAttribute));
    }
    
    return descriptor;
  }
  
  ShaderDescriptor BuildFragmentShaderDescriptor(const spirv_cross::CompilerReflection & comp)
  {
    ShaderDescriptor descriptor{
      ._stage = ShaderStage::Fragment,
    };
      
      return descriptor;
  }
  
  VertexAttributeDescriptor BuildVertexAttributeDescriptor(const spirv_cross::CompilerReflection& comp, const spirv_cross::Resource& inputAttribute)
  {
    spirv_cross::SPIRType spvType =  comp.get_type(inputAttribute.type_id);
    
    
    return VertexAttributeDescriptor{
      ._location = comp.get_decoration(inputAttribute.id, spv::DecorationLocation),
      ._binding = comp.get_decoration(inputAttribute.id, spv::DecorationBinding),
      ._type = SPVTypeToForgeType(spvType.basetype, spvType.vecsize, spvType.columns),
      ._offset = comp.get_decoration(inputAttribute.id, spv::DecorationOffset)
    };
    
  }
  
  void PopulateVertexAttributeDescriptors(ShaderDescriptor& descriptor, const spirv_cross::CompilerReflection& comp, const spirv_cross::ShaderResources& resources)
  {
    
    for(const auto& inputAttribute : resources.stage_inputs)
    {
      descriptor._vertexDescriptor._attributes.push_back(BuildVertexAttributeDescriptor(comp, inputAttribute));
    }
  }
  
}

