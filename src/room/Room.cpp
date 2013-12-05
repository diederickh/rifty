#include <room/Room.h>
#include <stdio.h>
#include <glm/gtx/vector_access.hpp> 

Room::Room() 
  :room_size(10.0f)
  ,num_grid(10)
  ,grid_size(room_size / num_grid)
  ,drawer(*this)
{
  
}

Room::~Room() {
}

bool Room::setup() {

  createRoom();

  if(!drawer.setup()) {
    printf("Error: cannot setup the room drawer.\n");
    return false;
  }

  return true;
}

void Room::update() {
  this->rotate(0.5f, 0.0f, 1.0f, 0.0f);

  //particles.addForce(vec3(0.0, 0.0, -1));
  particles.update(1.0f/60.0f);
  updateVertices();
  drawer.update();
}

void Room::draw(float* pm, float* vm) {
  drawer.draw(pm, vm, mm());
}

void Room::createRoom() {                      

  // create particles
  int num_particles = (num_grid * num_grid) * 6;
  for(size_t i = 0; i < num_particles; ++i) {
    Particle* p = new Particle();
    particles.push_back(p);
  }

  // disable the corners
  particles[0]->enabled = false; // bottom left
  particles[num_grid-1]->enabled = false; // bottom right 
  particles[(num_grid*num_grid)-1]->enabled = false; // top right  
  particles[(num_grid*num_grid) - num_grid]->enabled = false;  // top left

  // fill our vertex buffer.
  vertices.assign(6 * (num_grid * num_grid * 6), VertexP());

  // position before creating springs
  position();

  // create springs: backwall
  size_t offset = 0;
  for(size_t j = 0; j < num_grid - 1; ++j) {
    for(size_t i = 0; i < num_grid - 1; ++i) {

      size_t dx_pa = offset + ((j + 0) * num_grid) + (i + 0); // bottom left
      size_t dx_pb = offset + ((j + 0) * num_grid) + (i + 1); // bottom right
      size_t dx_pc = offset + ((j + 1) * num_grid) + (i + 1); // top right
      size_t dx_pd = offset + ((j + 1) * num_grid) + (i + 0); // top left

      Particle* pa = particles[dx_pa];
      Particle* pb = particles[dx_pb];
      Particle* pc = particles[dx_pc];
      Particle* pd = particles[dx_pd];

      Spring* sa = new Spring(pa, pb);
      Spring* sb = new Spring(pb, pc);
      Spring* sc = new Spring(pc, pd);
      Spring* sd = new Spring(pd, pa);

      particles.addSpring(sa);
      particles.addSpring(sb);
      particles.addSpring(sc);
      particles.addSpring(sd);
    }
  }
  

  updateVertices();

  printf("grid_size: %f\n", grid_size);
  printf("num vertices: %ld\n", vertices.size());
}

// positions the vertices based on the current state.
void Room::position() {

  size_t dx_offset = 0;

#if 1
  // back wall
  for(int j = 0; j < num_grid; ++j) {
    for(int i = 0; i < num_grid; ++i) {
      size_t dx = dx_offset + j * num_grid + i;
      Particle* p = particles[dx];
      set(p->pos, 
          -(room_size * 0.5f) + (i * grid_size), 
          -(room_size * 0.5f) + (j * grid_size), 
          -(room_size * 0.5f)
          ); 
    }
  }
#endif

#if 1
  // right wall
  dx_offset += num_grid * num_grid;

  for(int j = 0; j < num_grid; ++j) {
    for(int i = 0; i < num_grid; ++i) {
      size_t dx = dx_offset + j * num_grid + i;
      Particle* p = particles[dx];
      set(p->pos, 
          (room_size * 0.5f) - grid_size,
          -(room_size * 0.5f) + (i * grid_size), 
          -(room_size * 0.5f) + (j * grid_size)
          ); 
    }
  }
#endif

#if 1
  // left wall
  dx_offset += num_grid * num_grid;

  for(int j = 0; j < num_grid; ++j) {
    for(int i = 0; i < num_grid; ++i) {
      size_t dx = dx_offset + j * num_grid + i;
      Particle* p = particles[dx];
      set(p->pos, 
          -(room_size * 0.5f),
          -(room_size * 0.5f) + (i * grid_size), 
          -(room_size * 0.5f) + (j * grid_size)
          ); 
    }
  }
#endif

#if 1
  // front wall
  dx_offset += num_grid * num_grid;

  for(int j = 0; j < num_grid; ++j) {
    for(int i = 0; i < num_grid; ++i) {
      size_t dx = dx_offset + j * num_grid + i;
      Particle* p = particles[dx];
      set(p->pos, 
          -(room_size * 0.5f) + (i * grid_size), 
          -(room_size * 0.5f) + (j * grid_size),
          (room_size * 0.5f) - grid_size
          ); 
    }
  }
#endif

#if 1
  // bottom wall
  dx_offset += num_grid * num_grid;

  for(int j = 0; j < num_grid; ++j) {
    for(int i = 0; i < num_grid; ++i) {
      size_t dx = dx_offset + j * num_grid + i;
      Particle* p = particles[dx];
      set(p->pos, 
          -(room_size * 0.5f) + (i * grid_size), 
          -(room_size * 0.5f),
          -(room_size * 0.5f) + (j * grid_size)
          ); 
    }
  }
#endif

#if 1
  // top wall
  dx_offset += num_grid * num_grid;

  for(int j = 0; j < num_grid; ++j) {
    for(int i = 0; i < num_grid; ++i) {
      size_t dx = dx_offset + j * num_grid + i;
      Particle* p = particles[dx];
      set(p->pos, 
          -(room_size * 0.5f) + (i * grid_size), 
          (room_size * 0.5f) - grid_size,
          -(room_size * 0.5f) + (j * grid_size)
          ); 
    }
  }
#endif

}


void Room::updateVertices() {

  // the 4 particles of a grid
  size_t particle_offset = 0;
  size_t particle_a = 0; // bottom left
  size_t particle_b = 0; // bottom right
  size_t particle_c = 0; // top right
  size_t particle_d = 0; // top left

  size_t vertex_offset = 0;

  Particle *pa, *pb, *pc, *pd = NULL;
  
  for(int k = 0; k < 6; ++k) {

    for(int j = 0; j < num_grid - 1; ++j) {
      for(int i = 0; i < num_grid - 1; ++i) {

        particle_a = particle_offset + ((j + 0) * num_grid) + (i + 0); // bottom left
        particle_b = particle_offset + ((j + 0) * num_grid) + (i + 1); // bottom right
        particle_c = particle_offset + ((j + 1) * num_grid) + (i + 1); // top right
        particle_d = particle_offset + ((j + 1) * num_grid) + (i + 0); // top left

        pa = particles[particle_a];
        pb = particles[particle_b];
        pc = particles[particle_c];
        pd = particles[particle_d];

        // bottom right triangle
        VertexP& va = vertices[vertex_offset++];
        VertexP& vb = vertices[vertex_offset++];      
        VertexP& vc = vertices[vertex_offset++];

        va.set(pa->pos);
        vb.set(pb->pos);
        vc.set(pc->pos);
      
        // top left triangle
        VertexP& vd = vertices[vertex_offset++];
        VertexP& ve = vertices[vertex_offset++];
        VertexP& vf = vertices[vertex_offset++];
      
        vd.set(pa->pos);
        ve.set(pc->pos);
        vf.set(pd->pos);
      }
    }
    particle_offset += (num_grid * num_grid) ;
  }
}


void Room::rotate(float degrees, float x, float y, float z) {
  model_matrix = glm::rotate(model_matrix, degrees, vec3(x, y, z));
}
