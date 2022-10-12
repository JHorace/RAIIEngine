//
// Created by James on 8/31/2022.
//

#ifndef RAIIENGINE_SWAPCHAIN_HPP
#define RAIIENGINE_SWAPCHAIN_HPP

#include "p_includes.hpp"
#include "surface.hpp"

namespace Forge
{
  
  struct Image
  {
    vk::Image image;
    vk::raii::ImageView view;
    vk::Format format;
  };
  
  class Swapchain
  {
  public:
    Swapchain(const vk::raii::Device & device,
              const Surface & surface);
    
    void Update();
    
    const vk::raii::SwapchainKHR & operator*() const;
    const Image & GetCurrentImage() const;
    const Image & GetImage(uint32_t index) const;
  private:
    
    vk::SwapchainCreateInfoKHR CIBuilder(const Surface & surface);
    
    vk::raii::SwapchainKHR _vkSwapchain;
    std::vector<Image> _images;
    vk::raii::Semaphore _imageAcquiredSemaphore;
    vk::raii::Fence _drawReadyFence;
    
    uint32_t currentImageIndex;
  };
}

#endif //RAIIENGINE_SWAPCHAIN_HPP
