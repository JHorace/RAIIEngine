// Created 2022
// James Sumihiro and Bryan Johnson
//


#include "engine_vk_factory.hpp"
#include "i_engine.hpp"


int main(int argc, char * argv[])
{
  
  Forge::EngineVKFactory factory;
  
  Forge::IEngine * engine = factory.CreateEngine();
  
  //engine->AddWindow(window);
  
  return 0;
}
