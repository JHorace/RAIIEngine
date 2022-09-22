// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_RENDERER_HPP
#define RAIIENGINE_RENDERER_HPP

#include "p_includes.hpp"
#include "logical_device.hpp"

namespace Forge
{
  class Renderer
  {
  public:
    Renderer();
    
    void Draw(LogicalDevice & device);
  private:
    uint32_t imageCount;
    vk::RenderingInfo _renderingInfo;
    vk::RenderingAttachmentInfo _colorAttachInfo;
    vk::RenderingAttachmentInfo _depthAttachInfo;
    vk::RenderingAttachmentInfo _stencilAttachInfo;
  };
}


#endif //RAIIENGINE_RENDERER_HPP
