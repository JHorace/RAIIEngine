// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "queue_manager.hpp"


namespace Forge
{
  QueueManager::QueueManager(vk::raii::PhysicalDevice const & physDevice) :
    _queueFamilies(physDevice.getQueueFamilyProperties())
  {
  }

  std::optional<uint32_t> QueueManager::FindQueueFamilyIndex(const vk::QueueFlags & flags) const
  {

    for (uint32_t i = 0; i < _queueFamilies.size(); ++i)
      if ((_queueFamilies[i].queueFlags & flags) == flags)
        return i;

    return {};
  };
}
