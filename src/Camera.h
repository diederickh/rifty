#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils.h"

class Camera {
 public:
  Camera();
  ~Camera();
  void translate(float x, float y, float z);  /* use "standard" coordinates .. so as if you were standing behind the camera, eg. cam.translate(0,0,10); moves 10m way from the object */
  float* pm();                                /* returns a pointer to the projection matrix */
  float* vm();                                /* returns a pointer to the view matrix */
 private:
  void update();                              /* updates the view matrix when necessary */
 private:
  glm::vec3 position;                         /* in world coordinates */
  glm::mat4 projection_matrix;
  glm::mat4 view_matrix;
  bool must_update;                           /* set to true when the view matrix must be updated */
};

#endif
