//
// Created by James on 8/31/2022.
//

#include "swapchain.hpp"

namespace Forge::Renderer
{

  vk::raii::SwapchainKHR CreateSwapChain(const Device::DeviceWrapper & deviceWrapper, const Renderer::Surface & surface)
  {
    auto surface_format = surface.GetPreferredImageFormat(deviceWrapper);
    auto extent = surface.GetSurfaceCapabilities(deviceWrapper).currentExtent;

    vk::SwapchainCreateInfoKHR swapchainCI
    {
      .surface = *surface._handle,
      .minImageCount = surface.GetMinImageCount(deviceWrapper),
      .imageFormat = surface_format.format,
      .imageColorSpace = surface_format.colorSpace,
      .imageExtent = extent,
      .imageArrayLayers = 1,
      .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
      .imageSharingMode = vk::SharingMode::eExclusive,
      .presentMode = surface.GetPreferredPresentMode(deviceWrapper)
    };

    return deviceWrapper._device.createSwapchainKHR(swapchainCI);
  }

  Swapchain::Swapchain(const Device::DeviceWrapper & deviceWrapper, const Renderer::Surface & surface) :
    _handle(CreateSwapChain(deviceWrapper, surface))
  {

  }
}