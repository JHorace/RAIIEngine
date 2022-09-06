//
// Created by James on 8/31/2022.
//

#ifndef RAIIENGINE_SWAPCHAIN_HPP
#define RAIIENGINE_SWAPCHAIN_HPP

#include "p_includes.hpp"
#include "surface.hpp"
#include "device_wrapper.hpp"

namespace Forge::Renderer
{
  class Swapchain
  {
  public:
    Swapchain(const Device::DeviceWrapper & deviceWrapper, const Renderer::Surface & surface);
  private:
    vk::raii::SwapchainKHR _handle;
  };
}

#endif //RAIIENGINE_SWAPCHAIN_HPP
