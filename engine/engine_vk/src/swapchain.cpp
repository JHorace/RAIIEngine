// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "swapchain.hpp"

namespace Forge
{
  
  vk::SwapchainCreateInfoKHR CIBuilder(const vk::raii::PhysicalDevice & physDevice,
                                       const Surface & surface)
  {
    auto surface_format = surface.GetPreferredImageFormat(physDevice);
    auto extent = surface.GetSurfaceCapabilities(physDevice).currentExtent;
    
    return
      {
        .surface = **surface,
        .minImageCount = surface.GetMinImageCount(physDevice),
        .imageFormat = surface_format.format,
        .imageColorSpace = surface_format.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = vk::SharingMode::eExclusive,
        .presentMode = surface.GetPreferredPresentMode(physDevice)
      };
  }
  
  Swapchain::Swapchain(const vk::raii::PhysicalDevice & physDevice,
                       const LogicalDevice & device,
                       const Surface & surface)
    :
    _vkSwapchain{*device, CIBuilder(physDevice, surface)}
  {
  
  }
  
  const vk::raii::SwapchainKHR & Swapchain::operator*() const
  {
    return _vkSwapchain;
  }
}