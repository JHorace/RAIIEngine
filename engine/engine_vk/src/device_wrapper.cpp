// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "device_wrapper.hpp"

namespace Forge
{
  vk::raii::Device CreateDeviceFromPhysicalDevice(
    vk::raii::PhysicalDevice const & physDevice,
    QueueManager const & queueManager,
    std::vector<const char *> extensions = std::vector<const char *>{},
    std::vector<const char *> layers = std::vector<const char *>{});

  Device::Device(
    const vk::raii::PhysicalDevice & physDevice,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
    :
    _queueManager(QueueManager(physDevice)),
    _vkDevice(CreateDeviceFromPhysicalDevice(physDevice, _queueManager, extensions, layers)),
    _vkPhysicalDevice(physDevice)
  {

  }

  vk::raii::Device CreateDeviceFromPhysicalDevice(
    vk::raii::PhysicalDevice const & physDevice,
    QueueManager const & queueManager,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
  {
    ///Currently, we only use a single graphics queue
    std::optional<uint32_t> graphicsQueueFamilyIndex = queueManager.FindQueueFamilyIndex(vk::QueueFlagBits::eGraphics);

    float graphicsQueuePriority = 0.0f;

    vk::DeviceQueueCreateInfo deviceQueueCI
    {
      .queueFamilyIndex = 1
    };
    deviceQueueCI.setQueuePriorities(graphicsQueuePriority);

    vk::DeviceCreateInfo deviceCI{};
    deviceCI.setQueueCreateInfos(deviceQueueCI);
    deviceCI.setPEnabledExtensionNames(DEFAULT_EXTENSIONS);

    return vk::raii::Device{ physDevice, deviceCI };
  }
}

