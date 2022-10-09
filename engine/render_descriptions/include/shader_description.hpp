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

struct VertexAttributeDescription
{
    unsigned _location;
    unsigned _binding;
    Format _format;
    unsigned _offset;
};

struct VertexInputDescription
{
  unsigned _binding;
  unsigned _stride;
};

struct VertexDescription
{
  VertexInputDescription _input;
  std::vector<VertexAttributeDescription> _attributes;
};

struct ShaderDescription
{
    std::filesystem::path  _spvFile;
    VertexDescription _vertexDescription;
};

#endif //RAIIENGINE_SHADER_DESCRIPTION_HPP
