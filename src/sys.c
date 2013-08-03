#include "sys.h"

#include <time.h>
#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

/* Internals */

int running = 1; // FIXME: get rid of this variable
static double the_zoom_factor = 1.0;
static GLFWwindow* the_window; // the main window
static cpSpace* the_space; // the physics space


/* Graphics setup */

void fix_aspect(GLFWwindow* win, int width, int height)
{
  double z = the_zoom_factor;
  double a = ((GLfloat)width / (GLfloat)height) * z; // aspect

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);

  if(width >= height) {
    glOrtho(-a, a, -z, z, -z, z);
  } else {
    glOrtho(-z, z, 1 / -a, 1 / a, -z, z);
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

  glEnableClientState(GL_VERTEX_ARRAY);

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


int start_gfx(const char* title, int width, int height)
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
  glfwSetWindowSizeCallback(the_window, fix_aspect);

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

double zoom()
{
  return the_zoom_factor;
}

double setzoom(double f)
{
  double ret = the_zoom_factor;
  the_zoom_factor = f;
  return ret;
}


/* Physics */

cpSpace* init_space(void)
{
  the_space = cpSpaceNew();
  return the_space;
}

cpSpace* current_space(void)
{
  return the_space;
}

int deinit_space(void)
{
  cpSpaceFree(the_space);
  return 0;
}

int remove_body(cpBody* body)
{
  if(body == NULL) {
    return -1; // nyurupo~
  }

  cpSpace* space;
  if(the_space != NULL) {
    space = the_space;
  } else {
    return -1;
  }

  cpBodyEachShape_b(body,
      ^(cpShape* s){
        cpSpaceRemoveShape(space, s);
        cpShapeFree(s);
      });
  cpSpaceRemoveBody(space, body);
  cpBodyFree(body);

  return 0;
}

