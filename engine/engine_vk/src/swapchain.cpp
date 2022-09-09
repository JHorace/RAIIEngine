// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "swapchain.hpp"

namespace Forge
{
  Swapchain::Swapchain(const vk::raii::Device & device,
                       const Surface & surface)
    :
    _vkSwapchain{device, CIBuilder(surface)}
  {}
  
  const vk::raii::SwapchainKHR & Swapchain::operator*() const
  {
    return _vkSwapchain;
  }
  
  vk::SwapchainCreateInfoKHR Swapchain::CIBuilder(const Surface & surface)
  {
    return vk::SwapchainCreateInfoKHR
      {
        .surface = **surface,
        .minImageCount = surface._minImageCount,
        .imageFormat = surface._surfaceFormat.format,
        .imageColorSpace = surface._surfaceFormat.colorSpace,
        .imageExtent = surface.GetExtent(),
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = vk::SharingMode::eExclusive,
        .presentMode = surface._presentMode
      };
  }
}