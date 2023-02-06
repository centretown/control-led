#pragma once

#include <stdint.h>
#include <string>

#include <yaml-cpp/yaml.h>
#include "base.h"

namespace glow
{
  enum : uint16_t
  {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
  };

  enum : uint16_t
  {
    Horizontal,
    Vertical,
    Diagonal
  };

  struct Pivot
  {
    uint16_t first = 0;
    uint16_t last = 0;
    uint16_t offset = 0;
  };

  struct Coordinates
  {
    uint16_t row;
    uint16_t column;
  };

  class Grid
  {
  public:
    enum : uint8_t
    {
      LENGTH,
      ROWS,
      ORIGIN,
      ORIENTATION,
      KEY_COUNT,
    };

  private:
    uint16_t length = 0;
    uint16_t rows = 1;
    uint16_t origin = TopLeft;
    uint16_t orientation = Horizontal;

    uint16_t columns = 0;
    Pivot pivot;
    div_t point{0, 0};

  public:
    bool setup(uint16_t p_length,
               uint16_t p_rows = 1,
               uint8_t p_origin = TopLeft,
               uint8_t p_orientation = Horizontal);

    bool setup();

    uint16_t get_length() const ALWAYS_INLINE { return length; }
    uint16_t get_rows() const ALWAYS_INLINE { return rows; }
    uint16_t get_origin() const ALWAYS_INLINE { return origin; }
    uint16_t get_orientation() const ALWAYS_INLINE { return orientation; }
    uint16_t get_columns() const ALWAYS_INLINE { return columns; }
    uint16_t get_first() const ALWAYS_INLINE { return pivot.first; }
    uint16_t get_offset() const ALWAYS_INLINE { return pivot.offset; }
    uint16_t get_last() const ALWAYS_INLINE { return pivot.last; }

    // bool set_length(uint16_t a_length) ALWAYS_INLINE
    // {
    //   length = a_length;
    //   return setup();
    // }
    // // void set_rows(uint16_t a_rows) ALWAYS_INLINE
    // {
    //   rows = a_rows;
    //   setup();
    // }
    // void set_origin(uint16_t a_origin) ALWAYS_INLINE
    // {
    //   origin = a_origin;
    //   setup();
    // }
    // void set_orientation(uint16_t a_orientation) ALWAYS_INLINE
    // {
    //   orientation = a_orientation;
    //   setup();
    // }

    Coordinates map_coordinates(uint16_t offset)
    {
      Coordinates coord{0, 0};
      div_t result = div(offset, columns);
      return Coordinates{static_cast<uint16_t>(result.quot),
                         static_cast<uint16_t>(result.rem)};
    }

    uint16_t map(uint16_t index);
    uint16_t map_diagonal(uint16_t index);
    uint16_t map_diagonal_top(uint16_t index);
    uint16_t map_diagonal_bottom(uint16_t index);
    uint16_t map_to_origin(uint16_t offset);

    uint16_t map_columns(uint16_t i, div_t &point) ALWAYS_INLINE
    {
      point = div(i, rows);
      return (uint16_t)(point.rem * columns + point.quot);
    }

    uint16_t map_diagonal_middle(uint16_t index) ALWAYS_INLINE
    {
      div_t p = div(index - pivot.first, rows);
      return pivot.offset + p.quot +
             p.rem * (columns - 1);
    }

    static std::string keys[KEY_COUNT];
    friend YAML::convert<Grid>;
  };
}

namespace YAML
{
  using glow::Grid;

  template <>
  struct convert<Grid>
  {
    static Node encode(const Grid &grid)
    {
      Node node;
      node[Grid::keys[Grid::LENGTH]] = grid.length;
      node[Grid::keys[Grid::ROWS]] = grid.rows;
      node[Grid::keys[Grid::ORIGIN]] = grid.origin;
      node[Grid::keys[Grid::ORIENTATION]] = grid.orientation;
      return node;
    }

    static bool decode(const Node &node, Grid &grid)
    {
      if (!node.IsMap())
      {
        grid.setup();
        return false;
      }

      for (auto key = 0; key < Grid::KEY_COUNT; ++key)
      {
        Node item = node[Grid::keys[key]];
        if (!item.IsDefined())
        {
          continue;
        }

        switch (key)
        {
        case Grid::LENGTH:
          grid.length = item.as<uint16_t>();
          break;
        case Grid::ROWS:
          grid.rows = item.as<uint16_t>();
          break;
        case Grid::ORIGIN:
          grid.origin = item.as<uint16_t>();
          break;
        case Grid::ORIENTATION:
          grid.orientation = item.as<uint16_t>();
          break;
        }
      }

      return grid.setup();
    }
  };
}