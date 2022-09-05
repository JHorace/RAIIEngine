//
// Created by James on 8/27/2022.
//

#include "engine_vk_factory.hpp"

int main(void)
{
    EngineVKFactory factory;

    IEngine* engine = factory.CreateEngine();

    return 0;
}