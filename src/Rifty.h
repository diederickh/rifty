/*

  Some inspiration:
  -----------------
  - https://vimeo.com/50742359, "Apotheosis", nice simple colors + bloom
  - https://vimeo.com/53444911, "That will be the day", nice colors
  - https://vimeo.com/53089256, "Light", nice colors
  - https://vimeo.com/43841761, "ambient love2d", grayscale
  - https://vimeo.com/38378877, "Jagermeister rebirth", nice bright colors 

 */

#ifndef RIFTY_H
#define RIFTY_H

#include "Utils.h"
#include "Camera.h"

class Rifty {
 public:
  Rifty();
  ~Rifty();
  void update();
  void draw();
 public:
  Camera cam;
};

#endif
