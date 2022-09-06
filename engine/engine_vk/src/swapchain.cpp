// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "swapchain.hpp"

namespace Forge
{
  vk::raii::SwapchainKHR CreateSwapChain(const Device & device, const Surface & surface)
  {
    auto surface_format = surface.GetPreferredImageFormat(device);
    auto extent = surface.GetSurfaceCapabilities(device).currentExtent;

    vk::SwapchainCreateInfoKHR swapchainCI
    {
      .surface = *surface._vkSurface,
      .minImageCount = surface.GetMinImageCount(device),
      .imageFormat = surface_format.format,
      .imageColorSpace = surface_format.colorSpace,
      .imageExtent = extent,
      .imageArrayLayers = 1,
      .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
      .imageSharingMode = vk::SharingMode::eExclusive,
      .presentMode = surface.GetPreferredPresentMode(device)
    };

    return device._vkDevice.createSwapchainKHR(swapchainCI);
  }

  Swapchain::Swapchain(const Device & device, const Surface & surface) :
    _vkSwapchain(CreateSwapChain(device, surface))
  {

  }
}