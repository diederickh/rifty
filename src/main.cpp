#include <iostream>
 
#if defined(GLFW_INCLUDE_GLCOREARB)
#  undef GLFW_INCLUDE_GLCOREARB
#  define GFLFW_INCLUDE_NONE
#endif
 
#include <GLXW/glxw.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include "tinylib.h"

#include "Rifty.h"
#include "Utils.h"
#include "Road.h"
#include "Spline.h"

using namespace glm;
 
RiftyConfig rifty_config;
Rifty rifty;

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
void error_callback(int err, const char* desc);
void resize_callback(GLFWwindow* window, int width, int height);
 
int main() {

  rifty_config.data_path = "/Users/roxlu/Documents/programming/cpp/tests/oculus/install/bin/data/";

  glfwSetErrorCallback(error_callback);
 
  if(!glfwInit()) {
    printf("error: cannot setup glfw.\n");
    return false;
  }
 
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* win = NULL;
  int w = 1280;
  int h = 720;
 
  Road road;
  road.setup();

  win = glfwCreateWindow(w, h, "openGL", NULL, NULL);
  if(!win) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  Spline<vec3, 3> spline;
  spline.add(vec3(0.0, 0.0, 0.0));  
  spline.add(vec3(1.0, 1.0, 0.0));  
  spline.add(vec3(4.0, 2.0, 0.0));  
  spline.add(vec3(4.5, 4.0, 1.0));  
  spline.add(vec3(6.5, 2.4, 3.0));  
  float p = 0.00;
  for(int i = 0; i <= 100; ++i) {
    vec3 v = spline.get(p);
    printf("%f, %f, %f for %f\n", v[0], v[1], v[2], p);
    p += 0.01;
  }
 
  glfwSetFramebufferSizeCallback(win, resize_callback);
  glfwSetKeyCallback(win, key_callback);
  glfwMakeContextCurrent(win);
  glfwSwapInterval(1);
 
  if(glxwInit() != 0) {
    printf("error: cannot initialize glxw.\n");
    ::exit(EXIT_FAILURE);
  }
 
  while(!glfwWindowShouldClose(win)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rifty.update();
    rifty.draw();
 
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
 
  glfwTerminate();
 
  return EXIT_SUCCESS;
}
 
 
void error_callback(int err, const char* desc) {
  printf("glfw error: %s (%d)\n", desc, err);
}
 
void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
  
  if(action != GLFW_PRESS) {
    return;
  }
 
  switch(key) {
    case GLFW_KEY_LEFT: {
      break;
    }
    case GLFW_KEY_RIGHT: {
      break;
    }
    case GLFW_KEY_ESCAPE: {
      glfwSetWindowShouldClose(win, GL_TRUE);
      break;
    }
  };
  
}
 
void resize_callback(GLFWwindow* window, int width, int height) {
 
}
