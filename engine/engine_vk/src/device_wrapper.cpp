//
// Created by James on 8/31/2022.
//

#include "device_wrapper.hpp"

namespace Forge {
  namespace Device {
    vk::raii::Device CreateDeviceFromPhysicalDevice(vk::raii::PhysicalDevice const &physDevice,
                                                    QueueManager const &queueManager,
                                                    std::vector<const char *> extensions = std::vector<const char *>{},
                                                    std::vector<const char *> layers = std::vector<const char *>{});

    DeviceWrapper::DeviceWrapper(const vk::raii::PhysicalDevice &physDevice,
                                 std::vector<const char *> extensions,
                                 std::vector<const char *> layers)
      : _queueManager(QueueManager(physDevice)),
        _device(CreateDeviceFromPhysicalDevice(physDevice, extensions, layers)) {


    }

    vk::raii::Device CreateDeviceFromPhysicalDevice(vk::raii::PhysicalDevice const &physDevice,
                                                                   QueueManager const &queueManager,
                                                                   std::vector<const char *> extensions,
                                                                   std::vector<const char *> layers) {

      ///Currently, we only use a single graphics queue
      std::optional<uint32_t> graphicsQueueFamilyIndex = queueManager.FindQueueFamilyIndex(
        vk::QueueFlagBits::eGraphics);

      float graphicsQueuePriority = 0.0f;

      vk::DeviceQueueCreateInfo deviceQueueCI{
        .queueFamilyIndex = 1,
        .queueCount = 1,
        .pQueuePriorities= &graphicsQueuePriority
      };


      vk::DeviceCreateInfo deviceCI{
      };

      deviceCI.setPEnabledExtensionNames(DEFAULT_EXTENSIONS);

      return vk::raii::Device{physDevice, deviceCI};
    }

  }
}

