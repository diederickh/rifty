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
  void set(vec3& v) {  pos = v; }
  void set(float x, float y, float z) {  glm::set(pos, x, y, z);  }
  vec3 pos;
};

struct VertexPN {
  VertexPN(){}
  VertexPN(vec3 pos, vec3 norm):pos(pos),norm(norm) { }
  void set(vec3& v) { pos = v; } 
  void set(vec3& v, vec3& n) { pos = v; };
  void set(float x, float y, float z) { glm::set(pos, x, y, z); } 
  void set(float x, float y, float z, float nx, float ny, float nz) { glm::set(pos, x, y, z); glm::set(norm, nx, ny, nz); } 
  void setNorm(vec3& n) { norm = n; }
  vec3 pos;
  vec3 norm;
};


#endif
