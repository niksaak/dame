#include "sys.h"

#include <time.h>
#include <GLFW/glfw3.h>

/* Internals */

int running = 1;
double the_zoom_factor = 1.0;
double the_scr_aspect = 1.0;
GLFWwindow* the_window; // the main window

/* Graphics setup */

void on_resize(GLFWwindow* win, int width, int height)
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);

  the_scr_aspect = ((GLfloat)width / (GLfloat)height) * the_zoom_factor;
  if(width >= height) {
    glOrtho(-the_scr_aspect, the_scr_aspect, -1, 1, -1, 1);
  } else {
    glOrtho(-1, 1, 1 / -the_scr_aspect, 1 / the_scr_aspect, -1, 1);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void on_close(GLFWwindow* win)
{
  running = 0;
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


int setup_gfx(const char* title, int width, int height)
{
  if(!glfwInit()) {
    return -1;
  }
  // setting up window:
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  the_window = glfwCreateWindow(width, height, title, NULL, NULL);
  if(the_window == NULL) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(the_window);
  // setting callbacks:
  glfwSetWindowCloseCallback(the_window, on_close);
  glfwSetWindowSizeCallback(the_window, on_resize);

  setup_gl();
  //on_resize(the_window, width, height);
  return 0;
}

int stop_gfx(void) {
  glfwDestroyWindow(the_window);
  glfwTerminate();
  return 0;
}

/* Events */

int keypress(int key)
{
  if(glfwGetKey(the_window, key) == GLFW_PRESS) {
    return 1;
  }
  return 0;
}

int wait(double ms)
{
  struct timespec req = { 0, ms * 1000 };
  return nanosleep(&req, NULL);
}

/* Rendering */

int render(void)
{
  glfwSwapBuffers(the_window);
  glfwPollEvents();
  return 0;
}

double zoom(double factor)
{
  if(factor != 0) {
    the_zoom_factor = factor;
  }
  return the_zoom_factor;
}

