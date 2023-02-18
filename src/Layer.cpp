#include "Layer.h"

namespace glow
{
#ifndef STRIP_YAML
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