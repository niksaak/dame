#include "sys.h"

#include <time.h>
#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "draw.h"

/* Internals */


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

