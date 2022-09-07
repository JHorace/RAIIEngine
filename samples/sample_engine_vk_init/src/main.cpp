// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "engine_vk_factory.hpp"

int main(void)
{
    Forge::EngineVKFactory factory;

    Forge::IEngine * engine = factory.CreateEngine();

    system("pause");

    return 0;
}