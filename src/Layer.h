#pragma once

#include <string>

#ifndef MICRO_CONTROLLER
#include <yaml-cpp/yaml.h>
#endif

#include "base.h"
#include "Grid.h"
#include "Chroma.h"
#include "Filer.h"

namespace glow
{
  class Layer
  {
  public:
    enum : uint16_t
    {
      Relative = 0x8000, // horizontal
      Bounds = Relative,
    };

  private:
    uint16_t length = 0;
    uint16_t rows = 0;
    uint16_t begin = 0;
    uint16_t end = 0;
    Grid grid;
    Chroma chroma;
    uint16_t scan = 0;
    uint16_t position = 0;

  public:
    Layer() = default;

    Layer(uint16_t p_length,
          uint16_t p_rows,
          uint16_t p_begin,
          uint16_t p_end,
          const Grid &p_grid,
          const Chroma &p_chroma,
          uint16_t p_scan = 0)
    {
      setup(p_length, p_rows, p_begin, p_end, p_grid, p_chroma, p_scan);
    }

    uint16_t get_length() const ALWAYS_INLINE { return length; }
    uint16_t get_rows() const ALWAYS_INLINE { return rows; }
    uint16_t get_begin() const ALWAYS_INLINE { return begin; }
    uint16_t get_end() const ALWAYS_INLINE { return end; }
    const Grid &get_grid() const ALWAYS_INLINE { return grid; }
    const Chroma get_chroma() const ALWAYS_INLINE { return chroma; }
    uint16_t get_scan() const ALWAYS_INLINE { return scan; }

    bool setup()
    {
      if (length == 0)
      {
        return false;
      }

      if (rows == 0)
      {
        return false;
      }

      if (grid.setup_length(length, rows) == false)
      {
        return false;
      }

      if (chroma.setup_length(length) == false)
      {
        return false;
      }

      return true;
    }

    bool setup(uint16_t p_length,
               uint16_t p_rows,
               uint16_t p_begin,
               uint16_t p_end,
               const Grid &p_grid,
               const Chroma &p_chroma,
               uint16_t p_scan = 0)
    {
      length = p_length;
      rows = p_rows;
      begin = p_begin;
      end = p_end;
      grid = p_grid;
      chroma = p_chroma;
      scan = p_scan;
      return setup();
    }

    bool setup_length(uint16_t a_length, uint16_t a_rows = 1) ALWAYS_INLINE
    {
      length = a_length;
      rows = a_rows;
      return setup();
    }

    void get_position(uint16_t &first, uint16_t &last) ALWAYS_INLINE
    {
      if (scan > 0)
      {
        first = position;
        last = position + scan;

        position++;
        if (position >= length)
        {
          position = 0;
        }
        return;
      }

      first = begin;
      last = length - end;
    }

    template <typename LIGHT>
    void spin(LIGHT *light)
    {
      uint16_t first, last;
      get_position(first, last);

      for (uint16_t i = first; i < last; ++i)
      {
        light->put(grid.map(i), chroma.map(i));
        // light->get(grid.map(i)) = chroma.map(i);
      }
      chroma.update();
    }
    // friend Library;

#ifndef MICRO_CONTROLLER
    enum : uint8_t
    {
      LENGTH,
      ROWS,
      BEGIN,
      END,
      GRID,
      CHROMA,
      SCAN,
      KEY_COUNT,
    };

    static std::string keys[KEY_COUNT];
    friend YAML::convert<Layer>;
    std::string make_code();
#endif
  };
} // namespace glow

#ifndef MICRO_CONTROLLER
namespace YAML
{
  using namespace glow;

  template <>
  struct convert<Layer>
  {
    static void lookup(Node item, Chroma &chroma)
    {
      if (item.IsMap())
      {
        chroma = item.as<Chroma>();
        return;
      }

      std::string name = item.as<std::string>();
      if (load_yaml(custom_chroma(name), chroma))
      {
        return;
      }
      return;
    }

    static void lookup(Node item, Grid &grid)
    {
      if (item.IsMap())
      {
        grid = item.as<Grid>();
        return;
      }

      std::string name = item.as<std::string>();
      if (load_yaml(custom_grid(name), grid))
      {
        return;
      }
      return;
    }

    static Node encode(const Layer &layer)
    {
      Node node;
      node[Layer::keys[Layer::LENGTH]] = layer.length;
      node[Layer::keys[Layer::ROWS]] = layer.rows;
      node[Layer::keys[Layer::BEGIN]] = layer.begin;
      node[Layer::keys[Layer::END]] = layer.end;
      node[Layer::keys[Layer::GRID]] = layer.grid;
      node[Layer::keys[Layer::CHROMA]] = layer.chroma;
      node[Layer::keys[Layer::SCAN]] = layer.scan;
      return node;
    }

    static bool decode(const Node &node, Layer &layer)
    {
      if (!node.IsMap())
      {
        layer.setup();
        return false;
      }

      for (auto key = 0; key < Layer::KEY_COUNT; ++key)
      {
        Node item = node[Layer::keys[key]];
        if (!item.IsDefined())
        {
          continue;
        }

        switch (key)
        {
        case Layer::LENGTH:
          layer.length = item.as<uint16_t>();
          break;
        case Layer::ROWS:
          layer.rows = item.as<uint16_t>();
          break;
        case Layer::BEGIN:
          layer.begin = item.as<uint16_t>();
          break;
        case Layer::END:
          layer.end = item.as<uint16_t>();
          break;
        case Layer::GRID:
          lookup(item, layer.grid);
          break;
        case Layer::CHROMA:
          lookup(item, layer.chroma);
          break;
        case Layer::SCAN:
          layer.scan = item.as<uint16_t>();
          break;
        }
      }

      layer.setup();
      return true;
    }
  };
}
#endif