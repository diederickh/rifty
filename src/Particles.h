#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/vector_access.hpp> 
#include <glm/gtx/norm.hpp>

using namespace glm;

// -------------------------------------------------

class Particle {
 public:
  Particle();
  void addForce(const vec3& f);
 public:
  vec3 tmp_pos;
  vec3 pos;
  vec3 vel;
  vec3 forces;
  float inv_mass;
  bool enabled;
};

// -------------------------------------------------

class Spring { 
 public:
  Spring(Particle* a, Particle* b);
  void update(const float dt);  
 public:
  Particle* a;
  Particle* b;
  float rest_length;
  float curr_length;
  float k;
};


// -------------------------------------------------

class Particles {
 public: 

  Particles();
  ~Particles();

  void update(const float dt); /* integrates the particles */
  void addForce(const vec3& f);

  // vector management
  void push_back(Particle* p);
  size_t size();

  // springs
  void addSpring(Spring* s);

  // vector access
  typedef std::vector<Particle*>::iterator iterator;
  Particles::iterator begin();
  Particles::iterator end();
  Particle* operator[](size_t dx);

 public:
  std::vector<Particle*> particles; /* particles container; used by the drawer */
  std::vector<Spring*> springs;
};

inline void Particles::push_back(Particle* p) {
  particles.push_back(p);
}

inline size_t Particles::size() {
  return particles.size();
}

inline Particles::iterator Particles::begin() {
  return particles.begin();
}

inline Particles::iterator Particles::end() {
  return particles.end();
}

inline void Particles::addSpring(Spring* s) {
  springs.push_back(s);
}

inline Particle* Particles::operator[](size_t dx) {
#ifndef NDEBUG
  return particles.at(dx);
#else  
  return particles[dx];
#endif
}

#endif
