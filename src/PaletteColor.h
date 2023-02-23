#pragma once

#include <map>

#ifndef MICRO_CONTROLLER
#include <yaml-cpp/yaml.h>
#endif

#include "HSVColor.h"

namespace glow
{
  struct PaletteColor
  {
    enum : uint8_t
    {
      RGB,
      HSV,
      KEY_COUNT,
    };

    Color rgb;
    HSVColor hsv;
    static std::string keys[KEY_COUNT];
  };

  struct PaletteColorX
  {
    std::string name;
    PaletteColor color;
    PaletteColorX() = default;
    
    PaletteColorX(std::string p_name, PaletteColor p_color) : name(p_name), color(p_color) {}
  };
}

#ifndef MICRO_CONTROLLER
namespace YAML
{
  using glow::PaletteColor;

  template <>
  struct convert<PaletteColor>
  {
    static Node encode(const PaletteColor &palette)
    {
      Node node, rgb, hsv;
      node[PaletteColor::keys[PaletteColor::RGB]] = palette.rgb;
      node[PaletteColor::keys[PaletteColor::HSV]] = palette.hsv;
      return node;
    }

    static bool decode(const Node &node, PaletteColor &palette)
    {
      if (!node.IsMap())
      {
        return false;
      }
      palette.hsv = node[PaletteColor::keys[PaletteColor::HSV]].as<HSVColor>();
      palette.rgb = node[PaletteColor::keys[PaletteColor::RGB]].as<Color>();
      return true;
    }
  };
}
#endif // MICRO_CONTROLLER