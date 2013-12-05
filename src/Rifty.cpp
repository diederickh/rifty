#include "Rifty.h"

Rifty::Rifty() {
}

Rifty::~Rifty() {
}

bool Rifty::setup() {
  return room.setup();
}

void Rifty::update() {
  room.update();
}

void Rifty::draw() {
  room.draw(cam.pm(), cam.vm());
}
