/*

  Room
  ----
  Generates the vertices and keeps state of the room, which 
  is drawn by the RoomDrawer instance.
  
 */

#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <room/RoomDrawer.h>
#include <room/RoomEffect.h>
#include "Particles.h"
#include "Vertices.h"
#include "Types.h"

typedef VertexPN RoomParticleType;

class Room {
 public:
  Room();
  ~Room();
  bool setup();
  void update();
  void draw(float* pm, float* vm, float* nm); /* pm = projection matrix, vm = view matrix, nm = normal matrix */
  void rotate(float degrees, float xax, float yax, float zax); /* rotate the room, all in degrees */

  Particles& getParticles();
  Vertices<RoomParticleType>& getVertices();
  float* mm(); /* returns the model matrix */

 private:
  void position(); /* positions the particles for the 6 walls */
  void updateVertices(); /* based on the positions of the particles we position the triangles */  
  void createRoom(); /* creates the particles for the room */

 private:
  Particles particles;
  float room_size; /* size of the room */
  int num_grid; /* number of 'squares' per row/col */
  float grid_size; /* size per grid */
  RoomDrawer drawer;
  Vertices<RoomParticleType> vertices;
  mat4 model_matrix;

  std::vector<RoomEffect*> effects; /* effects that can be applied to the room, room will delete the effects in it's d'tor.  */
  RoomEffectNoise* effect_noise;
};

inline Particles& Room::getParticles() {
  return particles;
}

inline Vertices<RoomParticleType>& Room::getVertices() {
  return vertices;
}

inline float* Room::mm() {
  return value_ptr(model_matrix);
}

#endif
