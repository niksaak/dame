#include "demos.h"

#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "../event.h"
#include "../entity.h"
#include "../draw.h"
#include "../vector.h"

void demo1(void)
{
  double m_ball = 1;
  double r_ball = 0.05; // ball radius
  double i_ball = cpMomentForCircle(m_ball, 0, r_ball, cpvzero); // ball momentum
  cpSpace* space = init_space();
  cpBody* ball =
    cpSpaceAddBody(space, cpBodyNew(m_ball, i_ball));
  cpShape* shape =
    cpSpaceAddShape(space, cpCircleShapeNew(ball, r_ball, cpvzero));
  double step = 1.0 / 60;

  cpSpaceSetGravity(space, cpvzero);
  cpBodySetPos(ball, cpvzero);
  cpShapeSetFriction(shape, 0.7);

  while(!keypress(GLFW_KEY_SPACE) && !keypress(GLFW_KEY_Q)) {
    Vec pos = cpv2vec(cpBodyGetPos(ball));

    glClear(GL_COLOR_BUFFER_BIT);
    draw_circle(pos, r_ball);

    render();

    if(keypress(GLFW_KEY_UP)) {
      cpBodyApplyImpulse(ball, cpv(0, 0.05), cpvzero);
    }
    if(keypress(GLFW_KEY_DOWN)) {
      cpBodyApplyImpulse(ball, cpv(0, -0.05), cpvzero);
    }
    if(keypress(GLFW_KEY_LEFT)) {
      cpBodyApplyImpulse(ball, cpv(-0.05, 0), cpvzero);
    }
    if(keypress(GLFW_KEY_RIGHT)) {
      cpBodyApplyImpulse(ball, cpv(0.05, 0), cpvzero);
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

  deinit_space();
}

