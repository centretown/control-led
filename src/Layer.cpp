#include "Layer.h"

namespace glow
{
  std::string Layer::keys[Layer::KEY_COUNT] = {
      "length",
      "begin",
      "end",
      "grid",
      "chroma",
  };
}