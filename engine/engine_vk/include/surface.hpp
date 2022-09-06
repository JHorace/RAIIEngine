//
// Created by James on 8/31/2022.
//

#ifndef RAIIENGINE_SURFACE_HPP
#define RAIIENGINE_SURFACE_HPP

#include "p_includes.hpp"
#include "device_wrapper.hpp"

namespace Forge::Renderer
{
  class Surface
  {
  public:
    vk::SurfaceCapabilitiesKHR GetSurfaceCapabilities(const Device::DeviceWrapper & device) const;
    vk::PresentModeKHR GetPreferredPresentMode(const Device::DeviceWrapper & device) const;
    vk::SurfaceFormatKHR GetPreferredImageFormat(const Device::DeviceWrapper & device) const;
    uint32_t GetMinImageCount(const Device::DeviceWrapper & device) const;

    vk::raii::SurfaceKHR _handle;
  private:
    vk::SurfaceFormatKHR _surface_format;
    vk::Extent2D _extent;
  };
}

#endif //RAIIENGINE_SURFACE_HPP
