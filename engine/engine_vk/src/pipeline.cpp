// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "pipeline.hpp"

namespace Forge
{
  Pipeline::Pipeline(const vk::raii::Device & device,
                     const std::vector<vk::PipelineShaderStageCreateInfo> & shaderStageCIs)
    :
    _pipelineLayout{device, PipelineLayoutCIBuilder()},
    _pipeline{device, nullptr, PipelineCIBuilder(shaderStageCIs)}
  {}
  
  vk::PipelineLayoutCreateInfo Pipeline::PipelineLayoutCIBuilder()
  {
    vk::PipelineLayoutCreateInfo pipelineLayoutCI{
    
    };
    return pipelineLayoutCI;
  }
  
  vk::GraphicsPipelineCreateInfo Pipeline::PipelineCIBuilder(
    const std::vector<vk::PipelineShaderStageCreateInfo> & shaderStageCIs)
  {
    _colorAttachInfo = vk::RenderingAttachmentInfo{
      .imageLayout = vk::ImageLayout::eAttachmentOptimal,
      .loadOp = vk::AttachmentLoadOp::eClear,
      .storeOp = vk::AttachmentStoreOp::eStore,
    };
    
    _renderingInfo = vk::RenderingInfo{
      .renderArea = vk::Rect2D(),
      .layerCount = 1,
      .colorAttachmentCount = 1,
      .pColorAttachments = &_colorAttachInfo,
      .pDepthAttachment = nullptr,
      .pStencilAttachment = nullptr
    };
    
    vk::GraphicsPipelineCreateInfo graphicsPipelineCI{
      .pNext = nullptr,
      .stageCount = (uint32_t)shaderStageCIs.size(),
      .pStages = shaderStageCIs.data(),
      .pVertexInputState = &DefaultPipeline::emptyVertexInputCI,
      .pInputAssemblyState = &DefaultPipeline::inputAssemblyCI,
      .pViewportState = &DefaultPipeline::pipelineStateCI,
      .pRasterizationState = &DefaultPipeline::rasterizationCI,
      .pMultisampleState = &DefaultPipeline::multisampleCI,
      .pDepthStencilState = &DefaultPipeline::depthStencilCI,
      .pColorBlendState = &DefaultPipeline::colorBlendCI,
      .pDynamicState = &DefaultPipeline::dynamicStateCI,
      .layout = *_pipelineLayout,
      .renderPass = VK_NULL_HANDLE
    };
    
    return graphicsPipelineCI;
  }
  
  const vk::raii::Pipeline & Pipeline::operator*()
  {
    return _pipeline;
  }
}
