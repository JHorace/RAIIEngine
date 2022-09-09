// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_RENDERER_HPP
#define RAIIENGINE_RENDERER_HPP

#include "p_includes.hpp"
#include "swapchain.hpp"

namespace Forge
{
  class Renderer
  {
  public:
    Renderer(const vk::raii::Device & device,
             const Surface & surface);
  private:
    Swapchain _swapchain;
  };
}


#endif //RAIIENGINE_RENDERER_HPP
