#include <stdlib.h>
#include <stdio.h>

#include <GL/glfw.h>
#include "draw.h"

int running = 1;

vec2_t triangle[] = {
  { -1, -1 },
  {  0,  1 },
  {  1, -1 }
};

int draw_scene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw_polygon(triangle, 3);
  draw_circle((vec2_t){0,0}, 0.9);
  draw_square((vec2_t){0,0}, 1);
  return 0;
}

void demo1(void)
{
  cpSpace* space = cpSpaceNew();
  cpBody* ball =
    cpSpaceAddBody(space, cpBodyNew(1, cpMomentForCircle(1, 0, 0.1, cpvzero)));
  cpShape* shape = cpSpaceAddShape(space, cpCircleShapeNew(ball, 0.1, cpvzero));
  double step = 1.0 / 60;

  cpSpaceSetGravity(space, cpvzero);
  cpBodySetPos(ball, cpvzero);
  cpShapeSetFriction(shape, 0.7);

  while(glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE && running) {
    cpVect vec = cpBodyGetPos(ball);
    vec2_t pos = { vec.x, vec.y };

    glClear(GL_COLOR_BUFFER_BIT);
    draw_circle(pos, 0.1);
    glfwSwapBuffers();

    if(glfwGetKey(GLFW_KEY_UP)) {
      cpBodyApplyImpulse(ball, cpv(0, 0.1), cpvzero);
    }
    if(glfwGetKey(GLFW_KEY_DOWN)) {
      cpBodyApplyImpulse(ball, cpv(0, -0.1), cpvzero);
    }
    if(glfwGetKey(GLFW_KEY_LEFT)) {
      cpBodyApplyImpulse(ball, cpv(-0.1, 0), cpvzero);
    }
    if(glfwGetKey(GLFW_KEY_RIGHT)) {
      cpBodyApplyImpulse(ball, cpv(0.1, 0), cpvzero);
    }
    if(glfwGetKey('C')) {
      cpBodyResetForces(ball);
      cpBodySetVel(ball, cpvzero);
    }

    cpSpaceStep(space, step);
    glfwSleep(step);
  }
}

// tecs

int main(int argc, char** argv)
{
  int glfw_ver[3] = {0};
  int ogl_ver[2] = {0};

  glfwGetVersion(&glfw_ver[0], &glfw_ver[1], &glfw_ver[2]);
  glGetIntegerv(GL_MAJOR_VERSION, &ogl_ver[0]);
  glGetIntegerv(GL_MINOR_VERSION, &ogl_ver[1]);
  printf("Hello, world!\n");
  printf("Using GLFW %i.%i.%i\n", glfw_ver[0], glfw_ver[1], glfw_ver[2]);
  if(setup_gfx(512, 512)) {
    return 1;
  }
  /*
  while(glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE && running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_polygon(triangle, 3);
    draw_circle((vec2_t){0,0}, 0.9);
    draw_square((vec2_t){0,0}, 1);
    render();
  }
  */
  demo1();
  glfwTerminate();

  return 0;
}

