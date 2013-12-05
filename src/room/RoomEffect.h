#ifndef ROOM_EFFECT_H
#define ROOM_EFFECT_H

#include <glm/glm.hpp>
#include "Particles.h"
#include "Perlin.h"

class Room;

// --------------------------------------------

#define ROOM_EFFECT_NONE 0
#define ROOM_EFFECT_NOISE 1

// --------------------------------------------

class RoomEffect {
 public:
  RoomEffect(int name, Room& room);
  virtual void update(float dt) = 0;
 public:
  Room& room;
  int name;
};

// --------------------------------------------

class RoomEffectNoise : public RoomEffect {
 public:
  RoomEffectNoise(Room& room);
  void update(float dt);
 private:
  Perlin perlin;
  
};

#endif
