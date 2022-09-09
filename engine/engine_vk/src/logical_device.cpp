// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "logical_device.hpp"

namespace Forge
{
  
  LogicalDevice::LogicalDevice(
    const vk::raii::PhysicalDevice & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
    :
    _vkDevice{physDevice, CIBuilder(deviceQueueCI, extensions, layers)}
  {
  
  }
  
  const vk::raii::Device & LogicalDevice::operator*() const
  {
    return _vkDevice;
  }
  
  vk::DeviceCreateInfo LogicalDevice::CIBuilder(
    vk::DeviceQueueCreateInfo & deviceQueueCI,
    std::vector<const char *> & extensions,
    std::vector<const char *> & layers)
  {
    vk::DeviceCreateInfo deviceCI{};
    deviceCI.setQueueCreateInfos(deviceQueueCI);
    deviceCI.setPEnabledExtensionNames(extensions);
    deviceCI.setPEnabledLayerNames(layers);
    
    return deviceCI;
  }
  
  void LogicalDevice::CreateRendererFromSurface(const Surface & surface)
  {
    _renderers.emplace_back(Renderer(_vkDevice, surface));
  }
}

