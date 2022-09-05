//
// Created by James on 8/30/2022.
//

#ifndef RAIIENGINE_ENGINE_VK_FACTORY_HPP
#define RAIIENGINE_ENGINE_VK_FACTORY_HPP

#include "i_engine_factory.hpp"

class EngineVKFactory : public IEngineFactory
{
public:
    IEngine* CreateEngine() override;
    ~EngineVKFactory() override = default;
};

#endif //RAIIENGINE_ENGINE_VK_FACTORY_HPP
