#include "Frame.h"

namespace glow
{
#ifndef STRIP_YAML
  std::string Frame::keys[KEY_COUNT] = {
      "length",
      "interval",
      "layers",
  };
#endif
}
