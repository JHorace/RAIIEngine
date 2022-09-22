// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "debug.hpp"
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

namespace Forge
{
  Logger::Logger(vk::raii::Instance const & instance) :
    _messenger(CreateDebugUtilsMessenger(instance))
  {
    _info = spdlog::stdout_color_mt("info");
    _error = spdlog::stderr_color_mt("error");

  }

  vk::Bool32 Forge::Logger::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
    void * pUserData)
  {
    auto logger = static_cast<Logger *>(pUserData);
    logger->_info->info("Test message");
    logger->_info->flush();
    return 0;
  }

  vk::raii::DebugUtilsMessengerEXT Logger::CreateDebugUtilsMessenger(vk::raii::Instance const & instance)
  {
    vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCI
    {
      .messageSeverity = MESSAGE_SEVERITY,
      .messageType = MESSAGE_TYPE,
      .pfnUserCallback = &Forge::Logger::debugCallback,
      .pUserData = this
    };

    return instance.createDebugUtilsMessengerEXT(debugMessengerCI);
  }
}


