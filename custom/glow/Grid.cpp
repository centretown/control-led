#include "Grid.h"
#include <math.h>

namespace glow
{
#ifndef MICRO_CONTROLLER

  std::string Grid::make_code()
  {
    std::stringstream s;
    s << "{" << length << ","
      << rows << ","
      << origin << ","
      << orientation << "}";
    return s.str();
  }

  std::string Grid::keys[Grid::KEY_COUNT] = {
      "length",
      "rows",
      "origin",
      "orientation",
  };

  std::string Grid::origin_keys[ORIGIN_COUNT] = {
      "top left",
      "top right",
      "bottom left",
      "bottom right",
  };

  std::unordered_map<std::string, uint16_t> Grid::origin_map = {
      {origin_keys[TopLeft], TopLeft},
      {origin_keys[TopRight], TopRight},
      {origin_keys[BottomLeft], BottomLeft},
      {origin_keys[BottomRight], BottomRight},
  };

  std::string Grid::orientation_keys[ORIENTATION_COUNT] = {
      "horizontal",
      "vertical",
      "diagonal",
      "centred",
  };

  std::unordered_map<std::string, uint16_t> Grid::orientation_map = {
      {orientation_keys[Horizontal], Horizontal},
      {orientation_keys[Vertical], Vertical},
      {orientation_keys[Diagonal], Diagonal},
      {orientation_keys[Centred], Centred},
  };

#endif

  uint16_t Grid::adjust_bounds(float bound)
  {
    uint16_t scaled = static_cast<uint16_t>(round(bound));
    if (orientation == Horizontal)
    {
      return (scaled / columns) * columns;
    }

    return (scaled / rows) * rows;
  }

  bool Grid::setup()
  {
    if (length == 0)
    {
      return false;
    }

    if (rows == 0)
    {
      rows = 1;
    }

    columns = length / rows;

    if (orientation == Centred)
    {
      pivot.setup_centred(rows, columns);
    }
    else
    {
      pivot.setup_diagonal(rows, columns);
    }
    centre = (rows - 1) / 2 * columns + (columns - 1) / 2;
    return true;
  }

  bool Grid::setup(uint16_t p_length, uint16_t p_rows, uint8_t p_origin, uint8_t p_orientation)
  {
    length = p_length;
    rows = p_rows;
    origin = p_origin;
    orientation = p_orientation;
    return setup();
  }

  uint16_t Grid::map(uint16_t index)
  {
    uint16_t offset = index;
    if (orientation == Diagonal)
    {
      offset = map_diagonal(index);
    }
    else if (orientation == Vertical)
    {
      offset = map_columns(index);
    }
    else if (orientation == Centred)
    {
      offset = map_centred(index);
    }
    return map_to_origin(offset);
  }

  uint16_t Grid::map_diagonal_top(uint16_t index)
  {
    uint16_t offset = 0;
    uint16_t start = 0;
    while (start < index)
    {
      offset++;
      start += offset;
    }

    if (start == index)
    {
      return offset;
    }

    start -= offset;
    offset--;
    return offset + (index - start) * (columns - 1);
  }

  uint16_t Grid::map_diagonal_bottom(uint16_t index)
  {
    uint16_t offset = 2 * columns - 1;
    uint16_t start = pivot.last + 1;
    uint16_t increment = rows;
    while (start < index)
    {
      offset += columns;
      increment--;
      start += increment;
    }

    if (start == index)
    {
      return offset;
    }

    start -= increment;
    offset -= columns;
    return offset + (index - start) * (columns - 1);
  }

  uint16_t Grid::map_diagonal(uint16_t index)
  {
    if (columns < 3)
    {
      return index;
    }

    if (index < pivot.first)
    {
      return map_diagonal_top(index);
    }

    if (index <= pivot.last)
    {
      return map_diagonal_middle(index);
    }

    return map_diagonal_bottom(index);
  }

  uint16_t Grid::map_to_origin(uint16_t offset)
  {
    if (origin == BottomRight)
    {
      return length - offset - 1;
    }

    div_t point = div(offset, columns);

    // point.quot = row
    // point.rem = col

    if (origin == BottomLeft)
    {
      return (rows - point.quot - 1) * columns +
             point.rem;
    }

    if (origin == TopRight)
    {
      return point.quot * columns +
             (columns - point.rem - 1);
    }
    return offset;
  }

  uint16_t Grid::map_centred(uint16_t index)
  {
    if (index == 0)
    {
      return centre;
    }

    uint16_t ring = 1;
    int16_t ring_start = 1;
    int16_t ring_length = 8;
    for (;;)
    {
      if (ring_start + ring_length > index)
      {
        break;
      }
      ring++;
      ring_start += ring_length;
      ring_length += 8;
    }

    index -= ring_start;
    uint16_t side = index * 4 / ring_length;
    if (side == 0)
    {
      return centre + ring +
             (index - ring + 1) * columns;
    }

    index -= side * ring_length / 4;
    if (side == 1)
    {
      return centre + ring - 1 - index +
             ring * columns;
    }

    if (side == 2)
    {
      return centre - ring -
             (index - ring + 1) * columns;
    }

    return centre - ring + 1 + index -
           ring * columns;
  }

} // namespace glow
