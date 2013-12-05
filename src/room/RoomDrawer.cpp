#include "PCH.h"
#include <room/RoomDrawer.h>
#include <room/Room.h>


RoomDrawer::RoomDrawer(Room& room) 
  :room(room)
  ,vbo(0)
  ,vao(0)
  ,prog(0)
  ,vert(0)
  ,frag(0)
  ,frag_line(0)
  ,prog_line(0)
  ,u_pm(-1)
  ,u_vm(-1)
  ,u_mm(-1)
  ,u_nm(-1)
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
  glEnableVertexAttribArray(1); // norm
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPN), (GLvoid*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPN), (GLvoid*)12); /* 12 bytes offset */
  
  if(!createShader()) {
    return false;
  }

  if(!rgb_shift.setup()) {
    return false;
  }

  return true;
}

bool RoomDrawer::createShader() {
    
    
    std::string vsFile = GetFromResources("shaders/GBufferClearPass.vertex");
    std::string fsFile = GetFromResources( "shaders/GBufferClearPass.fragment" );
    Shader* vs = new Shader( GL_VERTEX_SHADER, ROOM_VS, strlen(ROOM_VS) );
    Shader* fs = new Shader( GL_FRAGMENT_SHADER, ROOM_FS, strlen(ROOM_FS) );
//    Shader* vs = new Shader( GL_VERTEX_SHADER, vsFile.c_str() );
//    Shader* fs = new Shader( GL_FRAGMENT_SHADER, fsFile.c_str() );
    ShaderProgram* prog2 = new ShaderProgram();
    prog2->AttachShader( vs );
    prog2->AttachShader( fs );
    prog2->Link();
    prog2->PrintParameters();
    delete vs;
    delete fs;
    delete prog2;
    
  vert = rx_create_shader(GL_VERTEX_SHADER, ROOM_VS);
  frag = rx_create_shader(GL_FRAGMENT_SHADER, ROOM_FS);
  frag_line = rx_create_shader(GL_FRAGMENT_SHADER, ROOM_LINE_FS);
  prog = rx_create_program(vert, frag);
  glBindAttribLocation(prog, 0, "a_pos");
  glBindAttribLocation(prog, 1, "a_norm");
  glLinkProgram(prog);

  u_pm = glGetUniformLocation(prog, "u_pm");
  u_vm = glGetUniformLocation(prog, "u_vm");
  u_mm = glGetUniformLocation(prog, "u_mm");
  u_nm = glGetUniformLocation(prog, "u_nm");
  assert(u_pm >= 0);
  assert(u_vm >= 0);
  assert(u_mm >= 0);
  assert(u_nm >= 0);

  // line program
  prog_line = rx_create_program(vert, frag_line);
  glBindAttribLocation(prog_line, 0, "a_pos");
  glBindAttribLocation(prog_line, 1, "a_norm");
  glLinkProgram(prog_line);

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

void RoomDrawer::draw(float* pm, float* vm, float* nm, float* mm) {

  glBindVertexArray(vao);

  // draw colors
  glUseProgram(prog);
  glUniformMatrix4fv(u_pm, 1, GL_FALSE, pm);
  glUniformMatrix4fv(u_vm, 1, GL_FALSE, vm);
  glUniformMatrix4fv(u_mm, 1, GL_FALSE, mm);
  glUniformMatrix3fv(u_nm, 1, GL_FALSE, nm);

  glDrawArrays(GL_TRIANGLES, 0, room.getVertices().size() );

  // lines
  glUseProgram(prog_line);
  glUniformMatrix4fv(glGetUniformLocation(prog_line, "u_pm"), 1, GL_FALSE, pm);
  glUniformMatrix4fv(glGetUniformLocation(prog_line, "u_vm"), 1, GL_FALSE, vm);
  glUniformMatrix4fv(glGetUniformLocation(prog_line, "u_mm"), 1, GL_FALSE, mm);
  glUniformMatrix3fv(glGetUniformLocation(prog_line, "u_nm"), 1, GL_FALSE, nm);

  //  glPointSize(3.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, room.getVertices().size() );
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
  rgb_shift.apply();
  rgb_shift.draw();
}
