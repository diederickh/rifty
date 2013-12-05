#include "Camera.h"

Camera::Camera() 
  :projection_matrix(glm::perspective(65.0f, 4.0f/3.0f, 0.1f, 100.0f))
  ,must_update(false)
{
  translate(0,0,15);
  vm();
}

Camera::~Camera() {
}

void Camera::translate(float x, float y, float z) {
  position[0] += x;
  position[1] += y;
  position[2] += z;
  must_update = true;
}

float* Camera::pm() {
  return glm::value_ptr(projection_matrix);
}

float* Camera::vm() {
  update();
  return glm::value_ptr(view_matrix);
}

void Camera::update() {

  if(!must_update) {
    return;
  }

  view_matrix[3][0] = -position[0];
  view_matrix[3][1] = -position[1];
  view_matrix[3][2] = -position[2];

  must_update = false;
  print(view_matrix);
}
