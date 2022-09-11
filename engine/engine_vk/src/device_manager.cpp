// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "device_manager.hpp"

namespace Forge
{
  
  DeviceManager::DeviceManager(vk::raii::PhysicalDevice physicalDevice)
    :
    _vkPhysicalDevice{std::move(physicalDevice)},
    _queueManager{_vkPhysicalDevice}
  {
  
  }
  
  const vk::raii::PhysicalDevice & DeviceManager::operator*() const
  {
    return _vkPhysicalDevice;
  }
  
  unsigned int DeviceManager::AddLogicalDevice(
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
  {
    auto queueFamilyIndex = _queueManager.FindQueueFamilyIndex(vk::QueueFlagBits::eGraphics);
    float queuePriority = 0;
    
    vk::DeviceQueueCreateInfo deviceQueueCI
      {
        .queueFamilyIndex = queueFamilyIndex.value(),
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
      };
    logicalDevices.emplace_back(LogicalDevice{_vkPhysicalDevice, deviceQueueCI, extensions, layers});
    return logicalDevices.size() - 1;
  }
  
  void DeviceManager::AddSurface(vk::raii::SurfaceKHR && surfaceHandle)
  {
    Surface surface(_vkPhysicalDevice, std::move(surfaceHandle));
    logicalDevices[0].CreateRendererFromSurface(surface);
  }
}