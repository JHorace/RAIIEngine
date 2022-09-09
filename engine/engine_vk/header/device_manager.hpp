// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_DEVICE_MANAGER_HPP
#define RAIIENGINE_DEVICE_MANAGER_HPP

#include "p_includes.hpp"
#include "queue_manager.hpp"
#include "logical_device.hpp"

namespace Forge
{
  
  class DeviceManager
  {
  public:
    explicit DeviceManager(vk::raii::PhysicalDevice physicalDevice);
    const vk::raii::PhysicalDevice & operator*() const;
    
    unsigned int AddLogicalDevice(
      std::vector<const char *> extensions,
      std::vector<const char *> layers);
    
    DeviceManager(DeviceManager && other) noexcept = default;
    DeviceManager(const DeviceManager &) = delete;
    DeviceManager operator=(const DeviceManager &) = delete;
  private:
    vk::raii::PhysicalDevice _vkPhysicalDevice;
    QueueManager _queueManager;
    std::vector<LogicalDevice> logicalDevices;
  };
}

#endif //RAIIENGINE_DEVICE_MANAGER_HPP
