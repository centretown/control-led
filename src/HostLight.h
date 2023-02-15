#pragma once

#include "base.h"
#include "RGBColor.h"
#include "DisplayANSI.h"

namespace glow
{
  static const size_t MAX_LIGHT_SIZE = 4096;
  class HostLight
  {
  public:
    uint16_t length = 1;
    uint16_t rows = 1;
    uint16_t columns = 1;
    Color colors[MAX_LIGHT_SIZE] = {{0, 0, 0}};

  public:
    HostLight(uint16_t p_length, uint16_t p_rows)
    {
      if (p_length > 0)
      {
        length = p_length;
      }
      if (p_rows > 0)
      {
        rows = p_rows;
      }
      columns = length / rows;
    }

    void row_col(uint16_t index, uint16_t &row, uint16_t &column) ALWAYS_INLINE
    {
      div_t d = div(index, columns);
      row = d.quot;
      column = d.rem;
    }

    void put(uint16_t index, Color color) ALWAYS_INLINE
    {
      colors[index % MAX_LIGHT_SIZE] = color;
      uint16_t row, column;
      row_col(index, row, column);
      DisplayANSI::put_light(row, column, color);
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
  };

} // namespace glow
