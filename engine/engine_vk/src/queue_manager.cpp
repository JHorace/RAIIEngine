//
// Created by James on 8/31/2022.
//

#include "queue_manager.hpp"


QueueManager::QueueManager(vk::raii::PhysicalDevice const &  physDevice)
: _queueFamilies(physDevice.getQueueFamilyProperties())
{}

std::optional<uint32_t> QueueManager::FindQueueFamilyIndex(const vk::QueueFlags &flags) const {

    for(uint32_t i = 0; i < _queueFamilies.size(); ++i)
    {
        if((_queueFamilies[i].queueFlags & flags) == flags)
            return i;
    }
    return {};
};

/* Deprecated
std::optional<QueueFamilyIndices> QueueManager::GetQueueFamilies(const vk::QueueFlags &queueFlags) {

    QueueFamilyIndices indices;
    vk::QueueFlags remainingBits = queueFlags;

    for(uint32_t i = 0; i < _queueFamilies.size(); ++i)
    {
        vk::QueueFlags matches = remainingBits & _queueFamilies[i].queueFlags;
        vk::QueueFlagBits::
        if(match)
    }


}
 */

