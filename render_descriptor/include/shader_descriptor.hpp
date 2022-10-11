//
// Created by jsumihiro on 10/8/22.
//

#ifndef RAIIENGINE_SHADER_DESCRIPTION_HPP
#define RAIIENGINE_SHADER_DESCRIPTION_HPP

#include <filesystem>
#include <vector>
#include "formats.hpp"

enum class ShaderStage
{
    Vertex,
    Fragment
};

struct VertexAttributeDescriptor
{
    unsigned _location;
    unsigned _binding;
    Forge::Format _format;
    unsigned _offset;
};

struct VertexInputDescriptor
{
  unsigned _binding;
  unsigned _stride;
};

struct VertexDescriptor
{
  VertexInputDescriptor _input;
  std::vector<VertexAttributeDescriptor> _attributes;
};

struct ShaderDescriptor
{
    ShaderStage _stage;
    VertexDescriptor _vertexDescriptor;
};

#endif //RAIIENGINE_SHADER_DESCRIPTION_HPP
