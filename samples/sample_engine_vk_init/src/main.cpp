// Created 2022
// James Sumihiro and Bryan Johnson
//


#include "engine_vk_factory.hpp"
#include "i_engine.hpp"
#include "GLFW/glfw3.h"

int main(int argc, char * argv[])
{
  glfwInit();
  
  Forge::EngineVKFactory factory;
  
  Forge::IEngine * engine = factory.CreateEngine();
  
  return 0;
}
