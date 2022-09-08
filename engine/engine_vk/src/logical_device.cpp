// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "logical_device.hpp"

namespace Forge
{
  vk::raii::Device CreateDeviceFromPhysicalDevice(
    vk::raii::PhysicalDevice const & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions = std::vector<const char *>{},
    std::vector<const char *> layers = std::vector<const char *>{});
  
  LogicalDevice::LogicalDevice(
    const vk::raii::PhysicalDevice & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
    :
    _vkDevice(CreateDeviceFromPhysicalDevice(physDevice, deviceQueueCI, extensions, layers))
  {
  
  }
  
  const vk::raii::Device & LogicalDevice::operator*() const
  {
    return _vkDevice;
  }
  
  vk::raii::Device CreateDeviceFromPhysicalDevice(
    vk::raii::PhysicalDevice const & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
  {
    vk::DeviceCreateInfo deviceCI{};
    deviceCI.setQueueCreateInfos(deviceQueueCI);
    deviceCI.setPEnabledExtensionNames(DEVICE_EXTENSIONS);
    
    return vk::raii::Device{physDevice, deviceCI};
  }
}

