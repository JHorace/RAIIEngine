// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_ENGINE_VK_HPP
#define RAIIENGINE_ENGINE_VK_HPP

#include "i_engine.hpp"
#include "p_includes.hpp"
#include "renderer.hpp"
#include "device_manager.hpp"

namespace Forge
{
  
  inline constexpr vk::ApplicationInfo APP_INFO
    {
      .pApplicationName = "TestApp",
      .applicationVersion = 1,
      .pEngineName = "Forge",
      .engineVersion = 1,
      .apiVersion = VK_API_VERSION_1_3,
    };
  
  class EngineVK : public IEngine
  {
  public:
    EngineVK(std::vector<const char *> extensions, std::vector<const char *> layers);

    void Render() override;
    virtual void AddWindow(WindowType window, MultiplexType instance) final;
  private:
    vk::InstanceCreateInfo CIBuilder(const vk::ApplicationInfo * appInfo,
                                     std::vector<const char *>& extensions,
                                     std::vector<const char *>& layers);
    bool CheckValidationLayerSupport(std::vector<const char *> const & validationLayers);

    vk::raii::Context _vkContext;
    vk::raii::Instance _vkInstance;
    std::vector<DeviceManager> _deviceManagers;
  };
}


#endif //RAIIENGINE_ENGINE_VK_HPP

