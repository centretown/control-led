#pragma once

#include <map>
#include "HSVColor.h"

namespace glow
{
  struct Crayon
  {
    Color rgb{0};
    HSVColor hsv{0};
  };

  extern std::map<std::string, Crayon> crayons;

  void build_crayons();
} // namespace glow
