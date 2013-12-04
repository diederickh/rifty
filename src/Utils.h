#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdio.h>
#include <stdint.h>
#include <glm/glm.hpp>

struct RiftyConfig {
  std::string data_path;
};

extern RiftyConfig rifty_config;

static std::string datapath() {
  return rifty_config.data_path;
}

static void print(glm::mat4& m) {
  printf("%f, %f, %f, %f\n", m[0][0], m[0][1], m[0][2], m[0][3]);
  printf("%f, %f, %f, %f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
  printf("%f, %f, %f, %f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
  printf("%f, %f, %f, %f\n", m[3][0], m[3][1], m[3][2], m[3][3]);
}


#endif
