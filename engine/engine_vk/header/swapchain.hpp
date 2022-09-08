//
// Created by James on 8/31/2022.
//

#ifndef RAIIENGINE_SWAPCHAIN_HPP
#define RAIIENGINE_SWAPCHAIN_HPP

#include "p_includes.hpp"
#include "surface.hpp"
#include "logical_device.hpp"

namespace Forge
{
  class Swapchain
  {
  public:
    Swapchain(const vk::raii::PhysicalDevice & physDevice, const LogicalDevice & device, const Surface & surface);
  
    const vk::raii::SwapchainKHR & operator*() const;
  private:
    vk::raii::SwapchainKHR _vkSwapchain;
  };
}

#endif //RAIIENGINE_SWAPCHAIN_HPP
