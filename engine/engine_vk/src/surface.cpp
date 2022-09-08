// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "surface.hpp"

namespace Forge
{
  vk::SurfaceCapabilitiesKHR Surface::GetSurfaceCapabilities(const vk::raii::PhysicalDevice & physDevice) const
  {
    return physDevice.getSurfaceCapabilitiesKHR(*_vkSurface);
  }

  vk::PresentModeKHR Surface::GetPreferredPresentMode(const vk::raii::PhysicalDevice & physDevice) const
  {
    auto presentModes = device._vkPhysicalDevice.getSurfacePresentModesKHR(*_vkSurface);

    if (std::find(presentModes.begin(), presentModes.end(), vk::PresentModeKHR::eMailbox) != presentModes.end())
      return vk::PresentModeKHR::eMailbox;
    else if (std::find(presentModes.begin(), presentModes.end(), vk::PresentModeKHR::eFifo) != presentModes.end())
      return vk::PresentModeKHR::eFifo;

    return vk::PresentModeKHR::eFifo;
  }

  vk::SurfaceFormatKHR Surface::GetPreferredImageFormat(const vk::raii::PhysicalDevice & physDevice) const
  {
    auto availableFormats = device._vkPhysicalDevice.getSurfaceFormatsKHR(*_vkSurface);

    for (const auto & format : availableFormats)
      if ((format.format == vk::Format::eB8G8R8A8Srgb) && (format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear))
        return format;

    // No suitable format found.
    return {};
  }

  uint32_t Surface::GetMinImageCount(const vk::raii::PhysicalDevice & physDevice) const
  {
    vk::SurfaceCapabilitiesKHR capabilities = GetSurfaceCapabilities(physDevice);

    return capabilities.minImageCount;
  }
  
  const vk::raii::SurfaceKHR & Surface::operator*() const
  {
    return _vkSurface;
  }
}