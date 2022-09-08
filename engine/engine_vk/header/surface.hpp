// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_SURFACE_HPP
#define RAIIENGINE_SURFACE_HPP

#include "p_includes.hpp"
#include "logical_device.hpp"

namespace Forge
{
  class Surface
  {
  public:
    vk::SurfaceCapabilitiesKHR GetSurfaceCapabilities(const vk::raii::PhysicalDevice & physDevice) const;
    vk::PresentModeKHR GetPreferredPresentMode(const vk::raii::PhysicalDevice & physDevice) const;
    vk::SurfaceFormatKHR GetPreferredImageFormat(const vk::raii::PhysicalDevice & physDevice) const;
    uint32_t GetMinImageCount(const vk::raii::PhysicalDevice & physDevice) const;
  
    const vk::raii::SurfaceKHR & operator*() const;
  
  private:
    vk::raii::SurfaceKHR _vkSurface;
    vk::SurfaceFormatKHR _surfaceFormat;
    vk::Extent2D _extent;
  };
}

#endif //RAIIENGINE_SURFACE_HPP
