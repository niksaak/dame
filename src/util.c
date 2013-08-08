#include "util.h"

int genid(void)
{
  static int id;
  return id++;
}

extern inline int ran_domo(int min, int max);

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

