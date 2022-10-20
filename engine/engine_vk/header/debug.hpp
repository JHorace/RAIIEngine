// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_DEBUG_HPP
#define RAIIENGINE_DEBUG_HPP

#include "p_includes.hpp"

namespace spdlog
{
  class logger;
}

namespace Forge
{

  inline constexpr vk::DebugUtilsMessageSeverityFlagsEXT MESSAGE_SEVERITY
  {
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
    //| vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
  };

  inline constexpr vk::DebugUtilsMessageTypeFlagsEXT MESSAGE_TYPE
  {
    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
  };

  class Logger
  {
  public:
    Logger(vk::raii::Instance const & instance);

    static vk::Bool32 debugCallback(
      VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
      VkDebugUtilsMessageTypeFlagsEXT messageType,
      const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
      void * pUserData);

    std::shared_ptr<spdlog::logger> _info;
    std::shared_ptr<spdlog::logger> _error;
  private:
    vk::raii::DebugUtilsMessengerEXT CreateDebugUtilsMessenger(vk::raii::Instance const & instance);
    vk::raii::DebugUtilsMessengerEXT _messenger;
  };
}


#endif //RAIIENGINE_DEBUG_HPP
