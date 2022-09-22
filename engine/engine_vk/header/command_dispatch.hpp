// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_COMMAND_DISPATCH_HPP
#define RAIIENGINE_COMMAND_DISPATCH_HPP

#include "p_includes.hpp"

namespace Forge
{
  class CommandDispatch
  {
  public:
    CommandDispatch(const vk::raii::Device & device,
                    uint32_t commandBufferCount,
                    uint32_t queueFamilyIndex);
  
  private:
    vk::CommandPoolCreateInfo CIBuilder(uint32_t queueFamilyIndex);
    vk::CommandBufferAllocateInfo AIBuilder(uint32_t commandBufferCount);
    
    vk::raii::CommandPool _vkCommandPool;
    vk::raii::CommandBuffers _vkCommandBuffers;
  };
}

#endif //RAIIENGINE_COMMAND_DISPATCH_HPP
