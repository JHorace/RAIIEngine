// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "device_manager.hpp"

namespace Forge
{
  
  bool IsPhysicalDeviceSuitable(vk::raii::PhysicalDevice const & physDevice)
  {
    vk::PhysicalDeviceProperties properties = physDevice.getProperties();
    vk::PhysicalDeviceFeatures features = physDevice.getFeatures();
    
    return (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu);
  }
  
  vk::raii::PhysicalDevice ChoosePhysicalDevice(vk::raii::Instance const & instance)
  {
    auto physDevices = instance.enumeratePhysicalDevices();
    
    for (auto const & physDevice: physDevices)
      if (IsPhysicalDeviceSuitable(physDevice))
        return physDevice;
  }
  
  DeviceManager::DeviceManager(const vk::raii::Instance & instance)
    :
    _vkPhysicalDevice{ChoosePhysicalDevice(instance)},
    _queueManager(_vkPhysicalDevice)
  {
    
    //logicalDevices.push_back(LogicalDevice(_vkPhysicalDevice, deviceCI, extensions, layers))
  }
  
  const vk::raii::PhysicalDevice & DeviceManager::GetPhysicalDevice() const
  {
    return _vkPhysicalDevice;
  }
  
}