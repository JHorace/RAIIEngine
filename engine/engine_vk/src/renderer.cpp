// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "renderer.hpp"

namespace Forge
{
  Renderer::Renderer(const vk::raii::Device & device,
                     const Surface & surface)
    :
    _swapchain(device, surface)
  {
  
  }
}