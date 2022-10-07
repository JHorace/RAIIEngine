// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "pipeline.hpp"

namespace Forge
{
  Pipeline::Pipeline(const vk::raii::Device & device)
  :
  _pipelineLayout{device, PipelineLayoutCIBuilder()},
  _pipeline{device, nullptr, PipelineCIBuilder()}
  {
  }
  
  vk::PipelineLayoutCreateInfo Pipeline::PipelineLayoutCIBuilder()
  {
    vk::PipelineLayoutCreateInfo pipelineLayoutCI{
    
    };
    return pipelineLayoutCI;
  }
  
  vk::GraphicsPipelineCreateInfo Pipeline::PipelineCIBuilder()
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
      .stageCount = 2, // TODO: make this more flexible
      .pVertexInputState = &DefaultPipeline::emptyVertexInputCI,
      .pInputAssemblyState = &DefaultPipeline::inputAssemblyCI,
      .pViewportState = &DefaultPipeline::pipelineStateCI,
      .pRasterizationState = &DefaultPipeline::rasterizationCI,
      .pMultisampleState = &DefaultPipeline::multisampleCI,
      .pDepthStencilState = &DefaultPipeline::depthStencilCI,
      .pColorBlendState = &DefaultPipeline::colorBlendCI,
      .pDynamicState = &DefaultPipeline::dynamicStateCI,
      .layout = *_pipelineLayout,
      .renderPass = nullptr
      //.stageCount = _shaderStageCIs.size(),
      //.pStages = _shaderStageCIs.data()
    };
    
    return graphicsPipelineCI;
  }
  
  
}
