// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_SURFACE_HPP
#define RAIIENGINE_SURFACE_HPP

#include "p_includes.hpp"
#include "device_wrapper.hpp"

namespace Forge
{
  class Surface
  {
  public:
    vk::SurfaceCapabilitiesKHR GetSurfaceCapabilities(const Device & device) const;
    vk::PresentModeKHR GetPreferredPresentMode(const Device & device) const;
    vk::SurfaceFormatKHR GetPreferredImageFormat(const Device & device) const;
    uint32_t GetMinImageCount(const Device & device) const;

    vk::raii::SurfaceKHR _vkSurface;
  private:
    vk::SurfaceFormatKHR _surfaceFormat;
    vk::Extent2D _extent;
  };
}

#endif //RAIIENGINE_SURFACE_HPP
