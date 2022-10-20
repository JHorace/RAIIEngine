// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_VERTEX_HPP
#define RAIIENGINE_VERTEX_HPP

#include <array>

namespace Forge
{
  struct Vertex
  {
    float x, y, z;
  };
  
  constexpr std::array unitTriangle
    {
      Vertex{-.5, -.5, .1},
      Vertex{.5, -.5, .1},
      Vertex{0, .5, .1}
    };
}

#endif //RAIIENGINE_VERTEX_HPP
