// Created 2022
// James Sumihiro and Bryan Johnson
//


#include "engine_vk_factory.hpp"
#include "i_engine.hpp"
#include "window_handler.hpp"
#include "GLFW/glfw3.h"
#include "cstdio"

// TODO: Move all this to an i_application / application_GLFW (replacing/superceding window_handler)

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char * argv[])
{
  if (!glfwInit())
  {
    return 1;
  }
  
  Forge::EngineVKFactory factory;
  
  Forge::IEngine * engine = factory.CreateEngine();
  
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  auto window = glfwCreateWindow(720, 480, "test", nullptr, nullptr);
  
  auto nWindow = Forge::NativeWindow(window);
  
  
  
  engine->AddWindow(Forge::NativeWindow(window));
  
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetErrorCallback(error_callback);
  
  while (!glfwWindowShouldClose(window))
  {

  }
  
  glfwTerminate();
  return 0;
}
