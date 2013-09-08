#include "draw.h"

#include <math.h>

static double zoom_factor = 1.0;
GLFWwindow* window; // the main window

/* GL */

// Helpers

static void fix_aspect(GLFWwindow* win, int width, int height)
{
  double z = zoom_factor;
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

static void on_close(GLFWwindow* win)
{ // TODO
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

// Sys:

int start_gfx(const char* title, int width, int height)
{
  if(!glfwInit()) {
    return -1;
  }
  // setting up window:
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if(window == NULL) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  // setting callbacks:
  glfwSetWindowCloseCallback(window, on_close);
  glfwSetWindowSizeCallback(window, fix_aspect);

  setup_gl();
  //on_resize(window, width, height);
  return 0;
}

int stop_gfx(void) {
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

const char* gl_strerror(GLenum error) {
  switch(error) {
    case GL_NO_ERROR:
      return "No error";
    case GL_INVALID_ENUM:
      return "Invalid enum";
    case GL_INVALID_OPERATION:
      return "Invalid operation";
    case GL_STACK_OVERFLOW:
      return "Stack overflow";
    case GL_STACK_UNDERFLOW:
      return "Stack underflow";
    case GL_OUT_OF_MEMORY:
      return "Out of memory";
    case GL_TABLE_TOO_LARGE:
      return "Table too large";
    default:
      break;
  }
  return "Unknown error";
}

GLFWwindow* current_window(void)
{
  return window;
}

// Rendering:

int render(void)
{
  glfwSwapBuffers(window);
  glfwPollEvents();
  return 0;
}

double zoom()
{
  return zoom_factor;
}

double setzoom(double f)
{
  double ret = zoom_factor;
  zoom_factor = f;
  return ret;
}

/* Drawing primitives */

int draw_points(const Vec coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  //glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_POINTS, 0, count);
  //glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polyline(const Vec coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  //glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_STRIP, 0, count);
  //glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polygon(const Vec coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  //glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_LOOP, 0, count);
  //glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

static Vec decasteljau(const Vec vects[], size_t count, double t)
{
  Vec v[count];

  for(int i = 0; i < count; i++) {
    v[i] = vects[i];
  }
  for(int k = 1; k < count; k++) {
    for(int i = 0; i < (count - k); i++) {
      v[i] = veclerp(v[i], v[i + 1], t);
    }
  }

  return v[0];
}

int draw_curve(const Vec coords[], size_t count)
{
  int segc = 0;
  int ret;
  Vec* curve;

  if(coords == NULL) {
    return -1; // nurupo~
  }
  for(int i = 0, j = 1; j < count; i++, j++) {
    segc += ceil(vecdist(coords[i], coords[j]) * 16);
  }
  curve = malloc(sizeof (Vec) * segc);
  if(curve == NULL) {
    return -1; // malloc error
  }
  for(int i = 0; i < segc; i++) {
    curve[i] = decasteljau(coords, count, (double)i / segc);
  }
  ret = draw_polyline(curve, segc);
  free(curve);
  return ret;
}

int draw_circle(Vec pos, double radius)
{ // drawing algorithm from here: http://slabode.exofire.net/circle_draw.shtml
  static Vec verts[360];
  static const size_t vertc = sizeof verts / sizeof (Vec);
  double theta = 2 * M_PI / vertc;
  double costh = cos(theta);
  double sinth = sin(theta);
  double t;
  double x = radius;
  double y = 0;

  for(int i = 0; i < vertc; i++) {
    verts[i].x = x + pos.x;
    verts[i].y = y + pos.y;

    t = x;
    x = costh * x - sinth * y;
    y = sinth * t + costh * y;
  }

  return draw_polygon(verts, vertc);
}

int draw_square(Vec pos, double side)
{
  GLdouble r = side / 2.0;
  GLdouble x = pos.x;
  GLdouble y = pos.y;
  Vec square[4] = {
    { x + r, y + r },
    { x + r, y - r },
    { x - r, y - r },
    { x - r, y + r }
  };

  return draw_polygon(square, 4);
}

int draw_rectangle(Vec pos, double width, double height)
{
  GLdouble cw = width / 2.0;
  GLdouble ch = height / 2.0;
  Vec square[4] = {
    { pos.x + cw, pos.y + ch },
    { pos.x + cw, pos.y - ch },
    { pos.x - cw, pos.y - ch },
    { pos.x - cw, pos.y + ch }
  };

  return draw_polygon(square, 4);
}

