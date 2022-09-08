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
    DeviceManager(const vk::raii::Instance & instance);
    const vk::raii::PhysicalDevice & GetPhysicalDevice() const;
    
    DeviceManager(const DeviceManager &) = delete;
    DeviceManager operator=(const DeviceManager &) = delete;
  private:
    vk::raii::PhysicalDevice _vkPhysicalDevice;
    QueueManager _queueManager;
    std::vector<LogicalDevice> logicalDevices;
  };
}

#endif //RAIIENGINE_DEVICE_MANAGER_HPP
