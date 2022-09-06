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
    EngineVK();

    void Render() override;

  private:
    vk::raii::Context _vkContext;
    vk::raii::Instance _vkInstance;

    std::vector<Renderer> _renderers;
  };
}


#endif //RAIIENGINE_ENGINE_VK_HPP

