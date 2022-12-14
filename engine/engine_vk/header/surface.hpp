// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_SURFACE_HPP
#define RAIIENGINE_SURFACE_HPP

#include "p_includes.hpp"

namespace Forge
{
  class Surface
  {
    // This needs to be first so _vkSurface is visible on member initialization.
    // TODO: Find a cleaner way to make this work or refactor.
    vk::raii::SurfaceKHR _vkSurface;
  public:
    // TODO: Pass raw window handle instead of surface.
    Surface(const vk::raii::PhysicalDevice & physicalDevice, vk::raii::SurfaceKHR && surface);
  
    const vk::raii::SurfaceKHR & operator*() const;
  
    Surface(Surface && other) noexcept = default;
    Surface(const Surface &) = delete;
    Surface operator=(const Surface &) = delete;
    
    const vk::SurfaceCapabilitiesKHR _surfaceCapabilities;
    const vk::PresentModeKHR _presentMode;
    const vk::SurfaceFormatKHR _surfaceFormat;
    const uint32_t _minImageCount;
  private:
    vk::SurfaceCapabilitiesKHR GetSurfaceCapabilities(const vk::raii::PhysicalDevice & physDevice) const;
    [[nodiscard]] vk::PresentModeKHR GetPreferredPresentMode(const vk::raii::PhysicalDevice & physDevice) const;
    vk::SurfaceFormatKHR GetPreferredImageFormat(const vk::raii::PhysicalDevice & physDevice) const;
    uint32_t GetMinImageCount(const vk::raii::PhysicalDevice & physDevice) const;
  };
}

#endif //RAIIENGINE_SURFACE_HPP
