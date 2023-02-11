#pragma once

#include <map>

#ifndef STRIP_YAML
#include <yaml-cpp/yaml.h>
#endif

#include "HSVColor.h"

namespace glow
{
  struct PaletteColor
  {
    enum : uint8_t
    {
      NAME,
      RGB,
      HSV,
      KEY_COUNT,
    };

    std::string name{};
    Color rgb{0};
    HSVColor hsv{0};
    static std::string keys[KEY_COUNT];
  };
}

#ifndef STRIP_YAML
namespace YAML
{
  using glow::PaletteColor;

  template <>
  struct convert<PaletteColor>
  {
    static Node encode(const PaletteColor &palette)
    {
      Node node, rgb, hsv;
      // node[PaletteColor::keys[PaletteColor::NAME]] = palette.name;
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
      // palette.name = node[PaletteColor::keys[PaletteColor::NAME]].as<std::string>();
      palette.hsv = node[PaletteColor::keys[PaletteColor::HSV]].as<HSVColor>();
      palette.rgb = node[PaletteColor::keys[PaletteColor::RGB]].as<Color>();
      return true;
    }
  };
}
#endif // STRIP_YAML