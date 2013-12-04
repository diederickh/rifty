#include "Camera.h"

Camera::Camera() 
  :projection_matrix(glm::perspective(35.0f, 1.0f, 0.1f, 100.0f))
  ,must_update(false)
{
  translate(0,0,5);
  vm();
}

Camera::~Camera() {
}

void Camera::translate(float x, float y, float z) {
  position[0] += -x;
  position[1] += -y;
  position[2] += -z;
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

  view_matrix[0][3] = position[0];
  view_matrix[1][3] = position[1];
  view_matrix[2][3] = position[2];
}
