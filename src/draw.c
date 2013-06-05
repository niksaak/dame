#include "draw.h"

#include <math.h>

#include "main.h"

/* Tools */

void GLFWCALL on_resize(int width, int height)
{
  GLfloat aspect = (GLfloat)width / (GLfloat)height;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
  if(width >= height) {
    glOrtho(-aspect, aspect, -1, 1, -1, 1);
  } else {
    glOrtho(-1, 1, 1 / -aspect, 1 / aspect, -1, 1);
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
  glAlphaFunc(GL_LEQUAL, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  return 0;
}

int setup_gfx(int width, int height)
{
  if(!glfwInit()) {
    return 1;
  }
  if(!glfwOpenWindow(width, height, 4, 4, 4, 4, 24, 8, GLFW_WINDOW)) {
    glfwTerminate();
    return 1;
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

/* Drawing primitives */

int draw_points(vec2_t* coords, size_t count)
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_POINTS, 0, count);
  glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polyline(vec2_t* coords, size_t count)
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_STRIP, 0, count);
  glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polygon(vec2_t* coords, size_t count)
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_LOOP, 0, count);
  glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

/*
int draw_circle(vec2_t pos, GLdouble radius)
{
  static vec2_t verts[512];
  static const size_t vertc = sizeof verts / sizeof (vec2_t);

  for(int i = 0; i < circle_vertc; i++) {
    GLdouble theta = 2.0 * M_PI * i / circle_vertc;
    circle_verts[i][0] = pos[0] + radius * cos(theta);
    circle_verts[i][1] = pos[1] + radius * sin(theta);
  }
  return draw_polygon(verts, vertc);
}
*/

int draw_circle(vec2_t pos, GLdouble radius)
{ // algorithm from here: http://slabode.exofire.net/circle_draw.shtml
  static vec2_t verts[360];
  static const size_t vertc = sizeof verts / sizeof (vec2_t);
  double theta = 2 * M_PI / vertc;
  double costh = cos(theta);
  double sinth = sin(theta);
  double t;
  double x = radius;
  double y = 0;

  for(int i = 0; i < vertc; i++) {
    verts[i][0] = x + pos[0];
    verts[i][1] = y + pos[1];

    t = x;
    x = costh * x - sinth * y;
    y = sinth * t + costh * y;
  }

  return draw_polygon(verts, vertc);
}

int draw_square(vec2_t pos, GLdouble side)
{
  GLdouble r = side / 2.0;
  GLdouble x = pos[0];
  GLdouble y = pos[1];
  vec2_t square[4] = {
    { x + r, y + r },
    { x + r, y - r },
    { x - r, y - r },
    { x - r, y + r }
  };

  return draw_polygon(square, 4);
}

