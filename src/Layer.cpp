#include "Layer.h"

namespace glow
{
#ifndef MICRO_CONTROLLER
  std::string Layer::make_code()
  {
    std::stringstream s;
    s << "{" << length << ","
      << rows << ","
      << begin << ","
      << end << ","
      << grid.make_code() << ","
      << chroma.make_code() << ","
      << scan << "}";
    return s.str();
  }

  std::string Layer::keys[Layer::KEY_COUNT] = {
      "length",
      "rows",
      "begin",
      "end",
      "grid",
      "chroma",
      "scan",
  };
#endif
}