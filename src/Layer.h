#pragma once

#include <stdint.h>
#include <string>
#include <yaml-cpp/yaml.h>

#include "base.h"
#include "Grid.h"
#include "Chroma.h"

namespace glow
{
  struct Layer
  {
    enum : uint8_t
    {
      LENGTH,
      BEGIN,
      END,
      GRID,
      CHROMA,
      KEY_COUNT,
    };

    uint16_t length = 10;
    uint16_t begin = 0;
    uint16_t end = 9;
    Grid grid;
    Chroma chroma;

    void setup(uint16_t p_length,
               uint16_t p_begin,
               uint16_t p_end,
               Grid &p_grid,
               Chroma &p_chroma)
    {
      set_range(p_length, p_begin, p_end);
      grid = p_grid;
      chroma = p_chroma;
    }

    void set_range(uint16_t p_length,
                   uint16_t p_begin,
                   uint16_t p_end)
    {
      if (p_length == 0)
      {
        return;
      }

      length = p_length;
      end = p_end % length;
      begin = p_begin % length;

      if (end < begin)
      {
        std::swap(begin, end);
      }
    }

    template <typename LIGHT>
    void spin(LIGHT *light)
    {
      for (uint16_t i = begin; i < end; ++i)
      {
        uint16_t offset = grid.map(i);
        light->get(offset) = chroma.map(i);
      }
      chroma.update_hue();
    }

    static std::string keys[KEY_COUNT];
  };
} // namespace glow

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
      if (!node.IsMap() || node.size() != 5)
      {
        return false;
      }

      layer.length =
          node[Layer::keys[Layer::LENGTH]].as<uint16_t>();
      layer.begin =
          node[Layer::keys[Layer::BEGIN]].as<uint16_t>();
      layer.end =
          node[Layer::keys[Layer::END]].as<uint16_t>();
      layer.grid =
          node[Layer::keys[Layer::GRID]].as<Grid>();
      layer.chroma =
          node[Layer::keys[Layer::CHROMA]].as<Chroma>();

      return true;
    }
  };
}