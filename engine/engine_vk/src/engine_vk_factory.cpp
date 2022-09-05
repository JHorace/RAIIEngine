//
// Created by James on 8/30/2022.
//

#include "../include/engine_vk_factory.hpp"
#include "../include/engine_vk.hpp"
#include "engine_vk.hpp"

IEngine *EngineVKFactory::CreateEngine() {
    return new Forge::EngineVK();
}
