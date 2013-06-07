#include "sys.h"

#include <GL/glfw.h>

#include "main.h"

/* Tools */

double zoom_factor = 1.0;
double scr_aspect = 1.0;

void GLFWCALL on_resize(int width, int height)
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);

  scr_aspect = ((GLfloat)width / (GLfloat)height) * zoom_factor;
  if(width >= height) {
    glOrtho(-scr_aspect, scr_aspect, -1, 1, -1, 1);
  } else {
    glOrtho(-1, 1, 1 / -scr_aspect, 1 / scr_aspect, -1, 1);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int GLFWCALL on_close(void)
{ // TODO: move this somewhere else
  running = 0;
  return 1;
}

static int setup_gl(void)
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 0);
  glClearDepth(1);

  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glAlphaFunc(GL_LEQUAL, 1);
  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(1.2);
  return 0;
}

int setup_gfx(int width, int height)
{
  if(!glfwInit()) {
    return -1;
  }
  if(!glfwOpenWindow(width, height, 4, 4, 4, 4, 24, 8, GLFW_WINDOW)) {
    glfwTerminate();
    return -1;
  }
  glfwSetWindowCloseCallback(on_close);
  glfwSetWindowSizeCallback(on_resize);
  setup_gl();
  on_resize(width, height);
  return 0;
}

int render(void)
{
  glfwSwapBuffers();
  return 0;
}

double zoom(double factor)
{
  if(factor != 0) {
    zoom_factor = factor;
  }
  return zoom_factor;
}

