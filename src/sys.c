#include "sys.h"

#include <time.h>
#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "draw.h"

/* Internals */

static cpSpace* space; // the physics space

/* Events */

int keypress(int key)
{
  if(glfwGetKey(current_window(), key) == GLFW_PRESS) {
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


/* Physics */

cpSpace* init_space(void)
{
  space = cpSpaceNew();
  return space;
}

cpSpace* current_space(void)
{
  return space;
}

int deinit_space(void)
{
  cpSpaceFree(space);
  return 0;
}

int remove_body(cpBody* body)
{
  if(body == NULL) {
    return -1; // nyurupo~
  }

  if(space == NULL) {
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

