#include "Particles.h"

// ------------------------------------------------------

Spring::Spring(Particle* a, Particle* b)
  :a(a)
  ,b(b)
  ,rest_length( distance2(b->pos,a->pos) )
  ,curr_length(rest_length)
  ,k(0.1f)
{

}

void Spring::update(const float dt) {
  vec3 dir = b->tmp_pos - a->tmp_pos;

  const float len = distance2(b->tmp_pos, a->tmp_pos);;
  const float inv_mass = a->inv_mass + b->inv_mass;
  const float f = ((rest_length - len) / inv_mass) * k;
  curr_length = len;

  dir /= len;
  dir *= f;
  dir *= dt;
 
  if(a->enabled) {
    a->tmp_pos -= (dir * a->inv_mass);
  }

  if(b->enabled) {
    b->tmp_pos += (dir * b->inv_mass);
  }
}

// ------------------------------------------------------

Particle::Particle()
  :enabled(true)
{
  inv_mass = 1.0f;
}

void Particle::addForce(const vec3& f) {
  forces += f;
}

// ------------------------------------------------------

Particles::Particles() {
}

Particles::~Particles() {

  for(Particles::iterator it = begin(); it != end(); ++it) {
    delete *it;
    it = particles.erase(it);
  }

  particles.clear();
  
}

void Particles::update(const float dt) {
  float drag = 0.99f;
  float fps = 1.0f / dt;

  // PREDICT NEW LOCATIONS
  for(Particles::iterator it = begin(); it != end(); ++it) {
    Particle* p = *it;

    if(!p->enabled) {
      p->tmp_pos = p->pos;
      continue;
    }

    p->vel = p->vel + (dt * p->forces);
    p->vel *= drag;

    p->tmp_pos = p->pos + (p->vel * dt);

    set(p->forces, 0.0f, 0.0f, 0.0f);
  }

  // CONSTRAINTS (@todo)
  const int k = 3;
  for(int i = 0; i < k; ++i) {
    for(std::vector<Spring*>::iterator it = springs.begin(); it != springs.end(); ++it) {
      Spring* s = *it;
      s->update(dt);
    }
  }

  // UPDATE VELOCITY AND POSITIONS
  for(Particles::iterator it = begin(); it != end(); ++it) {
    Particle* p = *it;

    if(!p->enabled) {
      continue;
    }

    p->vel = (p->tmp_pos - p->pos) * fps;
    p->pos = p->tmp_pos;
    set(p->tmp_pos, 0.0f, 0.0f, 0.0f);
  }
}

void Particles::addForce(const vec3& f) {
  for(Particles::iterator it = begin(); it != end(); ++it) {
    (*it)->addForce(f);
  }
}

