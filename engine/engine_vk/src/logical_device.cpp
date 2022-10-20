// Created 2022
// James Sumihiro and Bryan Johnson
//

#include <iostream>
#include "logical_device.hpp"
#include "utils.hpp"

namespace Forge
{
  const vk::SemaphoreCreateInfo semaphoreCI{
    .pNext = 0
  };
  const vk::FenceCreateInfo fenceCI{
    .pNext = 0,
    .flags = vk::FenceCreateFlagBits::eSignaled
  };
  
  LogicalDevice::LogicalDevice(
    const vk::raii::PhysicalDevice & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
    :
    _vkDevice{physDevice, CIBuilder(deviceQueueCI, extensions, layers)},
    _presentQueueFamilyIndex{deviceQueueCI.queueFamilyIndex},
    _commandDispatch{_vkDevice, 3, deviceQueueCI.queueFamilyIndex},
    _deviceMemoryManager{_vkDevice, physDevice.getMemoryProperties()},
    _imageAvailableSemaphore{_vkDevice, semaphoreCI},
    _presentReadySemaphore{_vkDevice, semaphoreCI},
    _drawReadyFence{_vkDevice, fenceCI}
  {
    auto & commandBuffer = _commandDispatch.GetCommandBuffer();
    const auto & queue = _vkDevice.getQueue(_presentQueueFamilyIndex, 0);
    
    _deviceMemoryManager.StageVBO(commandBuffer, queue);
  }
  
  void LogicalDevice::Update(const Surface & surface)
  {
    _swapchains[0].Update(_imageAvailableSemaphore);
    
    auto result = _vkDevice.waitForFences(*_drawReadyFence, true, 0);
    if (result == vk::Result::eSuccess)
    {
      _vkDevice.resetFences(*_drawReadyFence);
      Draw(surface);
      PresentToQueue();
    }
  }
  
  void LogicalDevice::Draw(const Surface & surface)
  {
    auto & commandBuffer = _commandDispatch.GetCommandBuffer();
    auto & currentImage = _swapchains[0].GetCurrentImage();
    const auto & queue = _vkDevice.getQueue(_presentQueueFamilyIndex, 0);
    
    commandBuffer.reset();
  
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
      //.clearValue = {std::array{0.f, 0.f, 0.f, 1.f}}
      .clearValue = {clearColors[currentImageIndex]}
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
    
    commandBuffer.bindVertexBuffers(0, **_deviceMemoryManager.GetVBO(), vk::DeviceSize{0});
    
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
  
    vk::PipelineStageFlags waitStage = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    
    vk::SubmitInfo submitInfo{
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &*_imageAvailableSemaphore,
      .pWaitDstStageMask = &waitStage,
      .commandBufferCount = 1,
      .pCommandBuffers = &*commandBuffer,
      .signalSemaphoreCount = 1,
      .pSignalSemaphores = &*_presentReadySemaphore
    };
    
    queue.submit(submitInfo, *_drawReadyFence);
  }
  
  void LogicalDevice::PresentToQueue()
  {
    const auto & queue = _vkDevice.getQueue(_presentQueueFamilyIndex, 0);
    
    uint32_t imageIndex = _swapchains[0].GetCurrentImageIndex();
    
    vk::PresentInfoKHR presentInfo{
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &*_presentReadySemaphore,
      .swapchainCount = 1,
      .pSwapchains = &(**_swapchains[0]),
      .pImageIndices = &imageIndex
    };
  
    auto result = queue.presentKHR(presentInfo);
  
    if (result == vk::Result::eSuccess)
    {}
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

