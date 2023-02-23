#include "Frame.h"

namespace glow
{
#ifndef MICRO_CONTROLLER
  std::string Frame::make_code()
  {
    std::stringstream s;
    s << "{" << length << ","
      << rows << ","
      << interval << ",//\n{";

    for (auto layer : layers)
    {
      s << layer.make_code() << ",\n";
    }

    s << "}}";

    return s.str();
  }

  std::string Frame::keys[KEY_COUNT] = {
      "length",
      "rows",
      "interval",
      "layers",
  };
#endif
}
