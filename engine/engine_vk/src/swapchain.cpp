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
  {
    auto images = _vkSwapchain.getImages();
    
    vk::ImageViewCreateInfo imageViewCreateInfo
      {
        .viewType = vk::ImageViewType::e2D,
        .format = surface._surfaceFormat.format,
        .components =
          {
            .r = vk::ComponentSwizzle::eR,
            .g = vk::ComponentSwizzle::eG,
            .b = vk::ComponentSwizzle::eB,
            .a = vk::ComponentSwizzle::eA
          },
        .subresourceRange =
          {
            .aspectMask = vk::ImageAspectFlagBits::eColor,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
          }
      };
    
    for (auto & image: images)
    {
      imageViewCreateInfo.image = image;
      _images.emplace_back(
        Image{image, vk::raii::ImageView(device, imageViewCreateInfo), surface._surfaceFormat.format});
    }
    
    
  }
  
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
        .imageExtent = surface._surfaceCapabilities.currentExtent,
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = vk::SharingMode::eExclusive,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .presentMode = surface._presentMode
      };
  }
  
  
  const Image & Swapchain::GetImage(uint32_t index) const
  {
    return _images[index];
  }
  
  void Swapchain::Update(vk::raii::Semaphore & imageAcquiredSemaphore)
  {
    // TODO change timeout to be non-zero?
    auto [result, image] = _vkSwapchain.acquireNextImage(1000000, *imageAcquiredSemaphore);
    
    if (result == vk::Result::eSuccess)
    {
      _currentImageIndex = image;
    }
  }
  
  uint32_t Swapchain::GetCurrentImageIndex() const
  {
    return _currentImageIndex;
  }
  
  const Image & Swapchain::GetCurrentImage() const
  {
    return _images[_currentImageIndex];
  }
  
}