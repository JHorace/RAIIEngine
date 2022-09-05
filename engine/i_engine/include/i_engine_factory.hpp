//
// Created by James on 8/30/2022.
//

#ifndef RAIIENGINE_I_ENGINE_FACTORY_HPP
#define RAIIENGINE_I_ENGINE_FACTORY_HPP

class IEngine;

class IEngineFactory
{
public:
    virtual ~IEngineFactory() {};
    virtual IEngine* CreateEngine() = 0;
};


#endif //RAIIENGINE_I_ENGINE_FACTORY_HPP
