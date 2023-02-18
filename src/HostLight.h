#pragma once

#include "base.h"
#include "RGBColor.h"
#include "DisplayANSI.h"

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

    void put(uint16_t index, Color color) ALWAYS_INLINE
    {
      if (index > MAX_LIGHT_SIZE)
      {
        return;
      }
      index = index % length;
      colors[index] = color;
    }

    // Color &get(uint16_t index) ALWAYS_INLINE
    // {
    //   // uint16_t row, column;
    //   // put(index, colors[index % MAX_LIGHT_SIZE]);
    //   // row_col(index, row, column);
    //   Color &color = colors[index % MAX_LIGHT_SIZE];
    //   put(index, color);
    //   return color;
    // }

    void update()
    {
      for (uint16_t i = 0; i < length; i++)
      {
        div_t d = div(i, columns);
        DisplayANSI::put_light(d.quot, d.rem, colors[i]);
      }
    }
  };

} // namespace glow
