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

  struct Grid
  {
    enum : uint8_t
    {
      LENGTH,
      ROWS,
      ORIGIN,
      ORIENTATION,
      KEY_COUNT,
    };

    uint16_t length = 10;
    uint16_t rows = 1;
    uint16_t origin = TopLeft;
    uint16_t orientation = Horizontal;

    uint16_t columns = 0;
    Pivot pivot;
    div_t point{0, 0};
    bool is_setup = false;

    bool setup(uint16_t p_length,
               uint16_t p_rows = 1,
               uint8_t p_origin = TopLeft,
               uint8_t p_orientation = Horizontal);

    bool setup();

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

    friend bool operator==(const Grid &a, const Grid &b)
    {
      return (a.length == b.length &&
              a.rows == b.rows &&
              a.origin == b.origin &&
              a.orientation == b.orientation &&
              a.pivot.first == b.pivot.first &&
              a.pivot.offset == b.pivot.offset &&
              a.pivot.last == b.pivot.last);
    }
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
      if (!node.IsMap() || node.size() != 4)
      {
        return false;
      }

      grid.length =
          node[Grid::keys[Grid::LENGTH]].as<uint16_t>();
      grid.rows =
          node[Grid::keys[Grid::ROWS]].as<uint16_t>();
      grid.origin =
          node[Grid::keys[Grid::ORIGIN]].as<uint16_t>();
      grid.orientation =
          node[Grid::keys[Grid::ORIENTATION]].as<uint16_t>();

      return grid.setup();
    }
  };
}