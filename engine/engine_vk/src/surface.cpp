//
// Created by James on 8/31/2022.
//

#include "surface.hpp"

namespace Forge::Renderer
{
  vk::SurfaceCapabilitiesKHR Surface::GetSurfaceCapabilities(const Device::DeviceWrapper & device) const
  {
    return device._physicalDevice.getSurfaceCapabilitiesKHR(*_handle);
  }

  vk::PresentModeKHR Surface::GetPreferredPresentMode(const Device::DeviceWrapper & device) const
  {
    auto presentModes = device._physicalDevice.getSurfacePresentModesKHR(*_handle);

    if (std::find(presentModes.begin(), presentModes.end(), vk::PresentModeKHR::eMailbox) != presentModes.end())
      return vk::PresentModeKHR::eMailbox;
    else if (std::find(presentModes.begin(), presentModes.end(), vk::PresentModeKHR::eFifo) != presentModes.end())
      return vk::PresentModeKHR::eFifo;

    return vk::PresentModeKHR::eFifo;
  }

  vk::SurfaceFormatKHR Surface::GetPreferredImageFormat(const Device::DeviceWrapper & device) const
  {
    auto availableFormats = device._physicalDevice.getSurfaceFormatsKHR(*_handle);

    for (const auto & format : availableFormats)
      if ((format.format == vk::Format::eB8G8R8A8Srgb) && (format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear))
        return format;

    return vk::SurfaceFormatKHR();
  }

  uint32_t Surface::GetMinImageCount(const Device::DeviceWrapper & device) const
  {
    vk::SurfaceCapabilitiesKHR capabilities = GetSurfaceCapabilities(device);

    return capabilities.minImageCount;
  }
}