// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_RENDERER_HPP
#define RAIIENGINE_RENDERER_HPP

#include "p_includes.hpp"
#include "logical_device.hpp"
#include "pipeline.hpp"

namespace Forge
{
  class Renderer
  {
  public:
    Renderer();
    
    void Draw(LogicalDevice & device, Pipeline & pipeline, WindowID windowID);
  private:
  
  };
}


#endif //RAIIENGINE_RENDERER_HPP
