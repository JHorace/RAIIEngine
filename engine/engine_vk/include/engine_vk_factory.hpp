// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_ENGINE_VK_FACTORY_HPP
#define RAIIENGINE_ENGINE_VK_FACTORY_HPP

#include <array>
#include "i_engine_factory.hpp"

inline constexpr std::array INSTANCE_EXTENSIONS
{
    "VK_KHR_surface"
};
inline constexpr std::array<const char *, 0> INSTANCE_LAYERS
{

};

namespace Forge
{
  class EngineVKFactory : public IEngineFactory
  {
  public:
    IEngine * CreateEngine() override;
    ~EngineVKFactory() override = default;
  };
}

#endif //RAIIENGINE_ENGINE_VK_FACTORY_HPP
