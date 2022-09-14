// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "engine_defaults.hpp"
#include "engine_vk_factory.hpp"
#include "engine_vk.hpp"

namespace Forge
{
  IEngine * EngineVKFactory::CreateEngine()
  {
    std::vector<const char *> extensions(INSTANCE_EXTENSIONS.begin(), INSTANCE_EXTENSIONS.end());
    std::vector<const char *> layers(INSTANCE_LAYERS.begin(), INSTANCE_LAYERS.end());

    return new Forge::EngineVK(extensions, layers);
  }
}
