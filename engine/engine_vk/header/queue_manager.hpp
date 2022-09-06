// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_QUEUE_MANAGER_HPP
#define RAIIENGINE_QUEUE_MANAGER_HPP

#include "p_includes.hpp"
#include <optional>

namespace Forge
{
  /// Stores the indices of the queue family or families selected to support operations requested by the client
  /// (graphics, compute, transfer, etc.)
  struct QueueFamilyIndices
  {
    std::optional<uint32_t> _graphicsIndex;
    std::optional<uint32_t> _computeIndex;
    std::optional<uint32_t> _graphicsComputeIndex;

  };

  /// Stores information about available queues and their capabilities. Current naive implementation will provide the
  /// first available queue family or families that support the required operations. Future implementation could allocate
  /// queue families based on usage
  class QueueManager
  {
  public:
    /// Constructs a QueueManager that will hold information about the queue families available to the given
    /// PhysicalDevice.
    /// \param physDevice
    QueueManager(vk::raii::PhysicalDevice const & physDevice);

    /// Finds the index of a queue family that supports all of the operations specified in flags.
    /// \param flags
    /// \return An optional containing the index of a queue family that supports all required operations, or an empty
    /// optional if no queue family supports all required operations
    std::optional<uint32_t> FindQueueFamilyIndex(vk::QueueFlags const & flags) const;

  private:
    std::vector<vk::QueueFamilyProperties> _queueFamilies;

    /* Deprecated
     *
     * public:
     *
     /// Finds and returns the indices of a set of queue families that can support the operations provided in queueFlags.
     /// Does not handle cases where no set of queue families support all the requested operations
     /// \param queueFlags
     /// \return
     std::optional<QueueFamilyIndices> GetQueueFamilies(vk::QueueFlags const & queueFlags);
     */
  };
}

#endif //RAIIENGINE_QUEUE_MANAGER_HPP
