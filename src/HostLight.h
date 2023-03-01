#pragma once
#ifndef ESPHOME_CONTROLLER

#include <iostream>

#include "base.h"
#include "RGBColor.h"
#include "ansi_stream.h"

namespace glow
{
  static const size_t MAX_LIGHT_SIZE = 8192;
  class HostLight
  {
  public:
    uint16_t length = 10;
    uint16_t rows = 1;
    uint16_t columns = 10;
    Color colors[MAX_LIGHT_SIZE] = {{0, 0, 0}};

  public:
    bool setup(uint16_t p_length, uint16_t p_rows)
    {
      if (p_length == 0 || p_length > MAX_LIGHT_SIZE)
      {
        return false;
      }

      length = p_length;

      if (p_rows == 0 || p_rows > length)
      {
        return false;
      }

      rows = p_rows;
      columns = length / rows;
      return true;
    }

    Color &get(uint16_t index) ALWAYS_INLINE
    {
      return colors[index % MAX_LIGHT_SIZE];
    }

    void update()
    {
      for (uint16_t i = 0; i < length; i++)
      {
        div_t d = div(i, columns);
        ansi_put_light(d.quot, d.rem, colors[i], std::cout);
      }
    }
  };

} // namespace glow
#endif