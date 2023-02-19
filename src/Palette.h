#pragma once

#include <map>

#ifndef MICRO_CONTROLLER
#include <yaml-cpp/yaml.h>
#endif

#include "PaletteColor.h"

namespace glow
{
  static HSVColor blank{};
  struct Palette
  {
    enum : uint8_t
    {
      TITLE,
      NOTES,
      COLORS,
      KEY_COUNT,
    };
    std::string title{};
    std::string notes{};
    std::map<std::string, PaletteColor> colors{};

    bool find_color(std::string color_name, PaletteColor &found);

    HSVColor lookup(std::string color_name)
    {
      PaletteColor found;
      if (find_color(color_name, found))
      {
        return found.hsv;
      }
      return blank;
    }

    static std::string keys[KEY_COUNT];
  };

}

#ifndef MICRO_CONTROLLER
namespace YAML
{
  using glow::Palette;
  template <>
  struct convert<Palette>
  {
    static Node encode(const Palette &palette)
    {
      Node node;
      node[Palette::keys[Palette::TITLE]] = palette.title;
      node[Palette::keys[Palette::NOTES]] = palette.notes;
      Node color_map = node[Palette::keys[Palette::COLORS]];
      for (auto item : palette.colors)
      {
        color_map[item.first] = item.second;
      }
      return node;
    }

    static bool decode(const Node &node, Palette &palette)
    {
      if (!node.IsMap())
      {
        return false;
      }

      palette.title =
          node[Palette::keys[Palette::TITLE]].as<std::string>();
      palette.notes =
          node[Palette::keys[Palette::NOTES]].as<std::string>();

      Node colors = node[Palette::keys[Palette::COLORS]];
      for (auto item : colors)
      {
        palette.colors[item.first.as<std::string>()] = item.second.as<PaletteColor>();
      }

      return true;
    }
  };
}
#endif // MICRO_CONTROLLER
