#pragma once

#include "base.h"
#include "stdint.h"

namespace glow
{
  struct Color
  {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t white = 0;

    Color(uint8_t p_red = 0, uint8_t p_green = 0, uint8_t p_blue = 0) ALWAYS_INLINE
    {
      red = p_red;
      green = p_green;
      blue = p_blue;
      white = 0;
    }

    inline bool operator==(const Color &color)
    {
      return (red == color.red &&
              green == color.green &&
              blue == color.blue);
    }
  };
} // namespace glow
