#pragma once

#include <string>
#include <sstream>
#include <map>
#include "Frame.h"

namespace glow
{
  struct Library
  {
    std::map<std::string, Frame> items;
    void add_frame(std::string name, Frame &frame)
    {
      items[name] = frame;
    }

    std::string make_source(std::string name);
  };
} // namespace glow
