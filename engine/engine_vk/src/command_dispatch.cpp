// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "command_dispatch.hpp"

namespace Forge
{
  
  CommandDispatch::CommandDispatch(const vk::raii::Device & device,
                                   uint32_t commandBufferCount,
                                   uint32_t queueFamilyIndex)
                                   :
    _vkCommandPool{device, CIBuilder(queueFamilyIndex)},
    _vkCommandBuffers{device, AIBuilder(commandBufferCount)}
  {
  
  }
  
  vk::CommandPoolCreateInfo CommandDispatch::CIBuilder(uint32_t queueFamilyIndex)
  {
    return vk::CommandPoolCreateInfo{
      .flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
      .queueFamilyIndex = queueFamilyIndex
    };
  }
  
  vk::CommandBufferAllocateInfo CommandDispatch::AIBuilder(uint32_t commandBufferCount)
  {
    return vk::CommandBufferAllocateInfo{
      .commandPool = *_vkCommandPool,
      .level = vk::CommandBufferLevel::ePrimary,
      .commandBufferCount = commandBufferCount
    };
  }
  
  vk::raii::CommandBuffer & CommandDispatch::GetCommandBuffer()
  {
    // TODO: manage command buffers somehow.
    return _vkCommandBuffers[0];
  }
}
