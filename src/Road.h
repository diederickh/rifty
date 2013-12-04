#ifndef ROAD_H
#define ROAD_H

#include <GLFW/glfw3.h>
#include <stdio.h>

class Road {
 public:
  Road();
  ~Road();
  bool setup();
 private:
  GLuint vbo;
  GLuint shader;
};

#endif
