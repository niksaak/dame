#include <stdlib.h>
#include <stdio.h>

#include <GLFW/glfw3.h>

#include "vector.h"
#include "sys.h"
#include "draw.h"

int running = 1;

cpVect triangle[] = {
  { -1, -1 },
  {  0,  1 },
  {  1, -1 }
};

void demo1(void)
{
  double m_ball = 1;
  double r_ball = 0.05; // ball radius
  double i_ball = cpMomentForCircle(m_ball, 0, r_ball, cpvzero); // ball momentum
  cpSpace* space = cpSpaceNew();
  cpBody* ball =
    cpSpaceAddBody(space, cpBodyNew(m_ball, i_ball));
  cpShape* shape =
    cpSpaceAddShape(space, cpCircleShapeNew(ball, r_ball, cpvzero));
  double step = 1.0 / 60;

  cpSpaceSetGravity(space, cpvzero);
  cpBodySetPos(ball, cpvzero);
  cpShapeSetFriction(shape, 0.7);

  while(!keypress(GLFW_KEY_SPACE) && !keypress(GLFW_KEY_Q) && running) {
    Vec pos = cpv2vec(cpBodyGetPos(ball));

    glClear(GL_COLOR_BUFFER_BIT);
    draw_circle(pos, r_ball);

    render();

    if(keypress(GLFW_KEY_UP)) {
      cpBodyApplyImpulse(ball, cpv(0, 0.1), cpvzero);
    }
    if(keypress(GLFW_KEY_DOWN)) {
      cpBodyApplyImpulse(ball, cpv(0, -0.1), cpvzero);
    }
    if(keypress(GLFW_KEY_LEFT)) {
      cpBodyApplyImpulse(ball, cpv(-0.1, 0), cpvzero);
    }
    if(keypress(GLFW_KEY_RIGHT)) {
      cpBodyApplyImpulse(ball, cpv(0.1, 0), cpvzero);
    }
    if(keypress(GLFW_KEY_ENTER)) {
      cpBodySetPos(ball, cpv(0, 0));
    }
    if(keypress(GLFW_KEY_C)) {
      cpBodyResetForces(ball);
      cpBodySetVel(ball, cpvzero);
    }

    cpSpaceStep(space, step);
    wait(step);
  }
}

int main(int argc, char** argv)
{
  int glfw_ver[3] = {0};
  int ogl_ver[2] = {0};

  glfwGetVersion(&glfw_ver[0], &glfw_ver[1], &glfw_ver[2]);
  glGetIntegerv(GL_MAJOR_VERSION, &ogl_ver[0]);
  glGetIntegerv(GL_MINOR_VERSION, &ogl_ver[1]);
  printf("Hello, world!\n");
  printf("Using GLFW %i.%i.%i\n", glfw_ver[0], glfw_ver[1], glfw_ver[2]);
  if(setup_gfx("Distance And Modular Entities",512, 512)) {
    return 1;
  }
  demo1();
  stop_gfx();

  return 0;
}

