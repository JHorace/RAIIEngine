// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "engine_vk_factory.hpp"
#include "engine_vk.hpp"

namespace Forge
{
  IEngine * EngineVKFactory::CreateEngine()
  {
    return new Forge::EngineVK();
  }
}
