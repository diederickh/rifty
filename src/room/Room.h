/*

  Room
  ----
  Generates the vertices and keeps state of the room, which 
  is drawn by the RoomDrawer instance.
  
 */

#ifndef ROOM_H
#define ROOM_H

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Particles.h"
#include <room/RoomDrawer.h>
#include "Vertices.h"
#include "Types.h"

class Room {
 public:
  Room();
  ~Room();
  bool setup();
  void update();
  void draw(float* pm, float* vm); /* pm = projection matrix, vm = view matrix */
  void rotate(float degrees, float xax, float yax, float zax); /* rotate the room, all in degrees */

  Particles& getParticles();
  Vertices<VertexP>& getVertices();
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
  Vertices<VertexP> vertices;
  mat4 model_matrix;
};

inline Particles& Room::getParticles() {
  return particles;
}

inline Vertices<VertexP>& Room::getVertices() {
  return vertices;
}

inline float* Room::mm() {
  return value_ptr(model_matrix);
}

#endif
