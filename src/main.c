#include <stdlib.h>
#include <stdio.h>

#include <GLFW/glfw3.h>

#include "vector.h"
#include "draw.h"
#include "demo/demos.h"

int main(int argc, char** argv)
{
  int glfwver[3] = {0};

  if(start_gfx("Distance And Modular Entities",512, 512)) {
    return 1;
  }
  glfwGetVersion(&glfwver[0], &glfwver[1], &glfwver[2]);
  printf("Using GL %s, GLSL %s\n",
         glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

  demo2();
  stop_gfx();

  return 0;
}

