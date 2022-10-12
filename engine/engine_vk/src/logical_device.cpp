// Created 2022
// James Sumihiro and Bryan Johnson
//

#include <iostream>
#include "logical_device.hpp"
#include "utils.hpp"

namespace Forge
{
  
  LogicalDevice::LogicalDevice(
    const vk::raii::PhysicalDevice & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
    :
    _vkDevice{physDevice, CIBuilder(deviceQueueCI, extensions, layers)},
    _presentQueueFamilyIndex{deviceQueueCI.queueFamilyIndex},
    _commandDispatch{_vkDevice, 3, deviceQueueCI.queueFamilyIndex}
  {
  }
  
  void LogicalDevice::Update(const Surface & surface)
  {
    Draw(surface);
  }
  
  void LogicalDevice::Draw(const Surface & surface)
  {
    auto & commandBuffer = _commandDispatch.GetCommandBuffer();
    auto & currentImage = _swapchains[0].GetImage(0);
  
    vk::CommandBufferBeginInfo beginInfo{};
    commandBuffer.begin(beginInfo);
    
    vk::ImageMemoryBarrier imageReadyBarrier{
      .pNext = nullptr,
      .dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite,
      .oldLayout = vk::ImageLayout::eUndefined,
      .newLayout = vk::ImageLayout::eColorAttachmentOptimal,
      .image = currentImage.image,
      .subresourceRange = {
        .aspectMask = vk::ImageAspectFlagBits::eColor,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1
      }
    };
    
    commandBuffer.pipelineBarrier(
      vk::PipelineStageFlagBits::eTopOfPipe,
      vk::PipelineStageFlagBits::eColorAttachmentOutput,
      vk::DependencyFlags{0},
      nullptr,
      nullptr,
      imageReadyBarrier
    );
    
    vk::RenderingAttachmentInfo renderingAttachmentInfo{
      .imageView = *currentImage.view,
      .imageLayout = vk::ImageLayout::eAttachmentOptimal,
      .loadOp = vk::AttachmentLoadOp::eClear,
      .storeOp = vk::AttachmentStoreOp::eStore,
      .clearValue = {std::array{1.f, 0.f, 0.f, 1.f}}
    };
    vk::RenderingInfo renderInfo{
      .renderArea = vk::Rect2D{{0}, surface._surfaceCapabilities.currentExtent},
      .layerCount = 1,
      .colorAttachmentCount = 1,
      .pColorAttachments = &renderingAttachmentInfo
    };
    commandBuffer.beginRendering(renderInfo);
  
    vk::Viewport viewport{
      .x = 0,
      .y = 0,
      .width = (float)surface._surfaceCapabilities.currentExtent.width,
      .height = (float)surface._surfaceCapabilities.currentExtent.height,
      .minDepth = 0,
      .maxDepth = 1
    };
    commandBuffer.setViewport(0, viewport); // 0 may not be valid.
  
    vk::Rect2D scissor{
      .offset = {0},
      .extent = surface._surfaceCapabilities.currentExtent
    };
    commandBuffer.setScissor(0, scissor);
    
    commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, **_pipelines[0]);
    
    commandBuffer.draw(3, 1, 0, 0);
    
    commandBuffer.endRendering();
    
    vk::ImageMemoryBarrier presentReadyBarrier{
      .srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite,
      .oldLayout = vk::ImageLayout::eAttachmentOptimal,
      .newLayout = vk::ImageLayout::ePresentSrcKHR,
      .image = currentImage.image,
      .subresourceRange = {
        .aspectMask = vk::ImageAspectFlagBits::eColor,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1
      }
    };
    commandBuffer.pipelineBarrier(
      vk::PipelineStageFlagBits::eColorAttachmentOutput,
      vk::PipelineStageFlagBits::eBottomOfPipe,
      vk::DependencyFlagBits::eByRegion,
      nullptr,
      nullptr,
      presentReadyBarrier
      );
    
    commandBuffer.end();
    
    const auto & queue = _vkDevice.getQueue(_presentQueueFamilyIndex, 0);
    
    vk::SubmitInfo submitInfo{
      .waitSemaphoreCount = 0,
      .pWaitSemaphores = nullptr,
      .commandBufferCount = 1,
      .pCommandBuffers = &(*commandBuffer),
      .signalSemaphoreCount = 0,
      .pSignalSemaphores = nullptr
    };
    
    queue.submit(submitInfo);
  }
  
  const vk::raii::Device & LogicalDevice::operator*() const
  {
    return _vkDevice;
  }
  
  vk::DeviceCreateInfo LogicalDevice::CIBuilder(
    vk::DeviceQueueCreateInfo & deviceQueueCI,
    std::vector<const char *> & extensions,
    std::vector<const char *> & layers)
  {
    _dynamicRenderingFeatures.dynamicRendering = true;
    
    vk::DeviceCreateInfo deviceCI{};
    deviceCI.setQueueCreateInfos(deviceQueueCI);
    deviceCI.setPEnabledExtensionNames(extensions);
    deviceCI.setPEnabledLayerNames(layers);
    deviceCI.setPNext(&_dynamicRenderingFeatures);
    
    return deviceCI;
  }
  
  void LogicalDevice::CreateSwapchainFromSurface(const Surface & surface)
  {
    _swapchains.emplace_back(Swapchain{_vkDevice, surface});
    
    CreateDefaultShaders(); // TODO: Move this somewhere else.
    CreateDefaultPipeline(); // TODO: Move this somewhere else.
  }
  
  CommandDispatch & LogicalDevice::GetDispatch()
  {
    return _commandDispatch;
  }
  
  const Swapchain & LogicalDevice::GetSwapchain(WindowID windowID) const
  {
    return _swapchains[windowID];
  }
  
  void LogicalDevice::CreateDefaultPipeline()
  {
    std::vector<vk::PipelineShaderStageCreateInfo> shaderCIs;
    
    shaderCIs.emplace_back(_shaders[0].CreateCI());
    
    _pipelines.emplace_back(Pipeline(_vkDevice, shaderCIs));
  }
  
  void LogicalDevice::CreateDefaultShaders()
  {
    auto vertBytes = LoadBinaryFile("./assets/shaders/spirv/simple.vert.spv");
    auto fragBytes = LoadBinaryFile("./assets/shaders/spirv/simple.frag.spv");
    
    _shaders.emplace_back(Shader(_vkDevice, vertBytes, Shader::Stage::vertex));
    _shaders.emplace_back(Shader(_vkDevice, fragBytes, Shader::Stage::fragment));
  }
}

