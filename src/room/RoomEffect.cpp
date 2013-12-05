#include <room/Room.h>
#include <room/RoomEffect.h>
  
// --------------------------------------------

RoomEffect::RoomEffect(int name, Room& room)
  :name(name)
  ,room(room)
{
}

// --------------------------------------------

RoomEffectNoise::RoomEffectNoise(Room& room) 
  :RoomEffect(ROOM_EFFECT_NOISE, room)
  ,perlin(4, 3.0f, 1.0f, 95)
{
}

void RoomEffectNoise::update(float dt) {
  static float time = 0.0f;
  time += (dt * 0.1);
  float f = 1.1f;
  Particles& p = room.getParticles();
  float dx = 0.0f;
  for(Particles::iterator it = p.begin(); it != p.end(); ++it) {
    Particle* particle = *it;
    particle->addForce(vec3(
                            perlin.get(dx + time) * f,  
                            perlin.get(dx + time + particle->pos[0]) * f, 
                            perlin.get(dx + time + particle->pos[1]) * f
                            ));
    dx += 0.01f;
  }
}
