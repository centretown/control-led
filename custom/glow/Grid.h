#pragma once

#include <stdint.h>
#include <string>
#include <unordered_map>

#include "base.h"
#ifndef MICRO_CONTROLLER
#include <yaml-cpp/yaml.h>
#include <sstream>
#endif

#include "Pivot.h"

namespace glow
{
  enum : uint16_t
  {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    ORIGIN_COUNT,
  };

  enum : uint16_t
  {
    Horizontal,
    Vertical,
    Diagonal,
    Centred,
    ORIENTATION_COUNT,
  };

  class Grid
  {
  private:
    uint16_t length = 0;
    uint16_t rows = 1;
    uint16_t origin = TopLeft;
    uint16_t orientation = Horizontal;

    uint16_t columns = 0;
    uint16_t centre = 0;
    Pivot pivot;

  public:
    Grid() = default;

    Grid(uint16_t p_length,
         uint16_t p_rows = 1,
         uint8_t p_origin = TopLeft,
         uint8_t p_orientation = Horizontal)
    {
      setup(p_length, p_rows, p_origin, p_orientation);
    }

    bool setup(uint16_t p_length,
               uint16_t p_rows = 1,
               uint8_t p_origin = TopLeft,
               uint8_t p_orientation = Horizontal);

    bool setup();

    bool setup_length(uint16_t p_length, uint16_t p_rows = 1) ALWAYS_INLINE
    {
      length = p_length;
      rows = p_rows;
      return setup();
    }

    uint16_t adjust_bounds(float bound);
    uint16_t get_length() const ALWAYS_INLINE { return length; }
    uint16_t get_rows() const ALWAYS_INLINE { return rows; }
    uint16_t get_origin() const ALWAYS_INLINE { return origin; }
    uint16_t get_orientation() const ALWAYS_INLINE { return orientation; }
    uint16_t get_columns() const ALWAYS_INLINE { return columns; }
    uint16_t get_first() const ALWAYS_INLINE { return pivot.first; }
    uint16_t get_offset() const ALWAYS_INLINE { return pivot.offset; }
    uint16_t get_last() const ALWAYS_INLINE { return pivot.last; }
    uint16_t get_centre() const ALWAYS_INLINE { return centre; }

    uint16_t map(uint16_t index);
    uint16_t map_diagonal(uint16_t index);
    uint16_t map_diagonal_top(uint16_t index);
    uint16_t map_diagonal_bottom(uint16_t index);
    uint16_t map_to_origin(uint16_t offset);

    uint16_t map_centred(uint16_t index);

    uint16_t map_columns(uint16_t index) ALWAYS_INLINE
    {
      div_t point = div(index, rows);
      return (uint16_t)(point.rem * columns + point.quot);
    }

    uint16_t map_diagonal_middle(uint16_t index) ALWAYS_INLINE
    {
      div_t point = div(index - pivot.first, rows);
      return pivot.offset + point.quot +
             point.rem * (columns - 1);
    }

#ifndef MICRO_CONTROLLER

    enum : uint8_t
    {
      LENGTH,
      ROWS,
      ORIGIN,
      ORIENTATION,
      KEY_COUNT,
    };

    static std::string keys[KEY_COUNT];
    static std::string origin_keys[ORIGIN_COUNT];
    static std::string orientation_keys[ORIENTATION_COUNT];
    static std::unordered_map<std::string, uint16_t> origin_map;
    static std::unordered_map<std::string, uint16_t> orientation_map;

    static bool match(
        std::string key,
        std::unordered_map<std::string, uint16_t> lookup,
        uint16_t &matched)
    {
      auto iter = lookup.find(key);
      if (iter == lookup.end())
      {
        return false;
      }
      matched = (uint16_t)iter->second;
      return true;
    }

    static bool match_origin(std::string key, uint16_t &matched)
    {
      return match(key, origin_map, matched);
    }
    static bool match_orientation(std::string key, uint16_t &matched)
    {
      return match(key, orientation_map, matched);
    }

    friend YAML::convert<Grid>;
    std::string make_code();

#endif // MICRO_CONTROLLER
  };
}

#ifndef MICRO_CONTROLLER

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
      node[Grid::keys[Grid::ORIGIN]] =
          Grid::origin_keys[grid.origin];
      node[Grid::keys[Grid::ORIENTATION]] =
          Grid::orientation_keys[grid.orientation];
      return node;
    }

    static bool decode(const Node &node, Grid &grid)
    {
      if (!node.IsMap())
      {
        grid.setup();
        return false;
      }

      uint16_t matched;

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
          if (Grid::match_origin(item.as<std::string>(), matched))
          {
            grid.origin = matched;
          }
          break;
        case Grid::ORIENTATION:
          if (Grid::match_orientation(item.as<std::string>(), matched))
          {
            grid.orientation = matched;
          }
          break;
        }
      }
      grid.setup();
      return true;
    }
  };
}
#endif // MICRO_CONTROLLER