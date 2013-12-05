#include <assert.h>
#include "Types.h"
#include "tinylib.h"
#include <room/RoomDrawer.h>
#include <room/Room.h>

RoomDrawer::RoomDrawer(Room& room) 
  :room(room)
  ,vbo(0)
  ,vao(0)
  ,prog(0)
  ,vert(0)
  ,frag(0)
  ,u_pm(-1)
  ,u_vm(-1)
  ,u_mm(-1)
{
}

RoomDrawer::~RoomDrawer() {
  printf("Error: need to destory all GL resources in RoomDrawer.\n");
}

bool RoomDrawer::setup() {

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0); // pos
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), (GLvoid*)0);
  
  if(!createShader()) {
    return false;
  }

  return true;
}

bool RoomDrawer::createShader() {
  vert = rx_create_shader(GL_VERTEX_SHADER, ROOM_VS);
  frag = rx_create_shader(GL_FRAGMENT_SHADER, ROOM_FS);
  prog = rx_create_program(vert, frag);
  glBindAttribLocation(prog, 0, "a_pos");
  glLinkProgram(prog);

  u_pm = glGetUniformLocation(prog, "u_pm");
  u_vm = glGetUniformLocation(prog, "u_vm");
  u_mm = glGetUniformLocation(prog, "u_mm");
  assert(u_pm >= 0);
  assert(u_vm >= 0);
  assert(u_mm >= 0);

  return true;
}

void RoomDrawer::update() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  size_t to_allocate = 0;
  if(room.getVertices().mustAllocate(to_allocate)) {
    glBufferData(GL_ARRAY_BUFFER, to_allocate, NULL, GL_STREAM_DRAW);
  }

  glBufferSubData(GL_ARRAY_BUFFER, 0, 
                  room.getVertices().getNumBytes(), 
                  room.getVertices().getPtr());
}

void RoomDrawer::draw(float* pm, float* vm, float* mm) {
  glBindVertexArray(vao);
  glUseProgram(prog);
  glUniformMatrix4fv(u_pm, 1, GL_FALSE, pm);
  glUniformMatrix4fv(u_vm, 1, GL_FALSE, vm);
  glUniformMatrix4fv(u_mm, 1, GL_FALSE, mm);

  glPointSize(3.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, room.getVertices().size() );
  //glDrawArrays(GL_POINTS, 0, room.getVertices().size());
}
