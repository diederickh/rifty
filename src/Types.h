/*

  Basic vertex types

 */
#ifndef RIFTY_TYPES_H
#define RIFTY_TYPES_H

#include <glm/glm.hpp>
#include <glm/gtx/vector_access.hpp> 

using namespace glm;

struct VertexP {

  VertexP(){}

  VertexP(vec3 pos):pos(pos) { }

  void set(vec3& v) {
    pos = v;
  }

  void set(float x, float y, float z) {
     glm::set(pos, x, y, z);
  }

  vec3 pos;
};

#endif
