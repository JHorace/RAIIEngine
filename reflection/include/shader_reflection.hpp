//
// Created by jsumihiro on 10/9/22.
//

#ifndef RAIIENGINE_REFLECT_HPP
#define RAIIENGINE_REFLECT_HPP

#include "shader_descriptor.hpp"
#include "spirv_cross/spirv_reflect.hpp"
ShaderDescriptor ReflectSPVShader(const std::vector<uint32_t>& spvBytes);
ShaderDescriptor ReflectSPVShader(const std::vector<char>& spvBytes);
ShaderDescriptor BuildVertexShaderDescriptor(ShaderDescriptor& descriptor, const spirv_cross::CompilerReflection& comp);
ShaderDescriptor BuildFragmentShaderDescriptor(const spirv_cross::CompilerReflection& comp);
VertexAttributeDescriptor BuildVertexAttributeDescriptor(const spirv_cross::CompilerReflection& comp, const spirv_cross::Resource& inputAttribute);
void PopulateVertexAttributeDescriptors(ShaderDescriptor& descriptor, const spirv_cross::CompilerReflection& comp, const spirv_cross::ShaderResources& resources);
//VertexInputDescriptor BuildVertexInputDescriptor()

#endif //RAIIENGINE_REFLECT_HPP
