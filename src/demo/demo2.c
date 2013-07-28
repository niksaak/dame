#include <stdlib.h>
#include <stdio.h>

#include <chipmunk/chipmunk.h>
#include <GLFW/glfw3.h>

#include "../draw.h"
#include "../vector.h"
#include "../util.h"
#include "../sys.h"
#include "../module.h"

static int issec(void)
{
  static int sec = 0;

  if(!(++sec % 60)) {
    return 1;
  }
  return 0;
}

void demo2(void)
{
  cpFloat step = 1000.0 / 60;
  cpFloat pow = 0.001;
  cpSpace* space = init_space();
  module_t* module = mkmodule(cpvzero);

  setzoom(8);
  while(!keypress(GLFW_KEY_Q) && running) {
    cpBody* body = module->body;
    cpVect vel = cpBodyGetVel(body);
    cpVect pos = cpBodyGetPos(body);
    GLenum error;

    if(issec()) {
      printf("vel: %s; ", cpvstr(vel));
      printf("pos: %s\n", cpvstr(pos));
    }

    if(keypress(GLFW_KEY_UP)) {
      cpBodyApplyImpulse(body, cpv(0, pow), cpvzero);
    }
    if(keypress(GLFW_KEY_DOWN)) {
      cpBodyApplyImpulse(body, cpv(0, -pow), cpvzero);
    }
    if(keypress(GLFW_KEY_LEFT)) {
      cpBodyApplyImpulse(body, cpv(-pow, 0), cpvzero);
    }
    if(keypress(GLFW_KEY_RIGHT)) {
      cpBodyApplyImpulse(body, cpv(pow, 0), cpvzero);
    }
    if(keypress(GLFW_KEY_SPACE)) {
      cpBodySetPos(body, cpvzero);
      cpBodySetVel(body, cpvzero);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    draw_module(module);
    render();
    if((error = glGetError())) {
      gl_strerror(error);
    }
    cpSpaceStep(space, step);
    wait(step);
  }
  kmmodule(module);
  deinit_space();
}

