#pragma once

#include <string>

#ifndef STRIP_YAML
#include <yaml-cpp/yaml.h>
#endif

#include "base.h"
#include "Grid.h"
#include "Chroma.h"

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
    uint16_t begin = 0;
    uint16_t end = 0;
    Grid grid;
    Chroma chroma;

  public:
    uint16_t get_length() const ALWAYS_INLINE { return length; }
    uint16_t get_begin() const ALWAYS_INLINE { return begin; }
    uint16_t get_end() const ALWAYS_INLINE { return end; }
    const Grid &get_grid() const ALWAYS_INLINE { return grid; }
    const Chroma get_chroma() const ALWAYS_INLINE { return chroma; }

    bool setup()
    {
      if (length == 0)
      {
        return false;
      }

      if (grid.setup_length(length) == false)
      {
        return false;
      }

      if (chroma.setup_length(length) == false)
      {
        return false;
      }

      if (end < begin)
      {
        std::swap(begin, end);
      }
      return true;
    }

    bool setup(uint16_t p_length,
               uint16_t p_begin,
               uint16_t p_end,
               const Grid &p_grid,
               const Chroma &p_chroma)
    {
      length = p_length;
      begin = p_begin;
      end = p_end;
      grid = p_grid;
      chroma = p_chroma;
      return setup();
    }

    bool setup_length(uint16_t a_length) ALWAYS_INLINE
    {
      length = a_length;
      return setup();
    }

    template <typename LIGHT>
    void spin(LIGHT *light)
    {
      for (uint16_t i = begin; i < length - end; ++i)
      {
        light->put(grid.map(i), chroma.map(i));
        // light->get(grid.map(i)) = chroma.map(i);
      }
      chroma.update_hue();
    }

#ifndef STRIP_YAML
    enum : uint8_t
    {
      LENGTH,
      BEGIN,
      END,
      GRID,
      CHROMA,
      KEY_COUNT,
    };

    static std::string keys[KEY_COUNT];
    friend YAML::convert<Layer>;
#endif
  };
} // namespace glow

#ifndef STRIP_YAML
namespace YAML
{
  using glow::Layer;

  template <>
  struct convert<Layer>
  {
    static Node encode(const Layer &layer)
    {
      Node node;
      node[Layer::keys[Layer::LENGTH]] = layer.length;
      node[Layer::keys[Layer::BEGIN]] = layer.begin;
      node[Layer::keys[Layer::END]] = layer.end;
      node[Layer::keys[Layer::GRID]] = layer.grid;
      node[Layer::keys[Layer::CHROMA]] = layer.chroma;
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
        case Layer::BEGIN:
          layer.begin = item.as<uint16_t>();
          break;
        case Layer::END:
          layer.end = item.as<uint16_t>();
          break;
        case Layer::GRID:
          layer.grid = item.as<Grid>();
          break;
        case Layer::CHROMA:
          layer.chroma = item.as<Chroma>();
          break;
        }
      }

      layer.setup();
      return true;
    }
  };
}
#endif