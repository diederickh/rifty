#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdint.h>

struct RiftyConfig {
  std::string data_path;
};

extern RiftyConfig rifty_config;

static std::string datapath() {
  return rifty_config.data_path;
}


#endif
