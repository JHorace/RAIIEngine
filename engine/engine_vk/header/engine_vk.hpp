// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_ENGINE_VK_HPP
#define RAIIENGINE_ENGINE_VK_HPP

#include "i_engine.hpp"
#include "p_includes.hpp"
#include "renderer.hpp"

namespace Forge
{
  class EngineVK : public IEngine
  {
  public:
    EngineVK(std::vector<const char *> extensions, std::vector<const char *> layers);

    void Render() override;
    void AddWindow(void * windowHandle);
  private:
    vk::DynamicLoader _dl;
    vk::raii::Context _vkContext;
    vk::raii::Instance _vkInstance;
    Device _device;

    std::vector<Renderer> _renderers;
  };
}


#endif //RAIIENGINE_ENGINE_VK_HPP

