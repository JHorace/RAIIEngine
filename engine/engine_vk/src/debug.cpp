//
// Created by James on 9/4/2022.
//

#include "debug.hpp"
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

namespace Forge
{
  namespace Debug
  {

    vk::raii::DebugUtilsMessengerEXT CreateDebugUtilsMessenger(vk::raii::Instance const& instance, Logger * logger);

    Logger::Logger(vk::raii::Instance const &instance) : _messenger(CreateDebugUtilsMessenger(instance, this))
    {
      _info = spdlog::stdout_color_mt("info");
      _error = spdlog::stderr_color_mt("error");

    }

    vk::Bool32 Forge::Debug::Logger::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                   VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                   const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                   void *pUserData)
    {
      auto logger = static_cast<Logger*>(pUserData);
      logger->_info->info("Test message");
      return 0;
    }

    vk::raii::DebugUtilsMessengerEXT CreateDebugUtilsMessenger(vk::raii::Instance const& instance, Logger * logger)
    {

      vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCI{
        .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
                           | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
        .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                       | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                       | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
        .pfnUserCallback = &Forge::Debug::Logger::debugCallback,
        .pUserData = logger
      };

      return instance.createDebugUtilsMessengerEXT(debugMessengerCI);
    }



  }
}


