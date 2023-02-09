#pragma once

#include <map>

#ifndef USE_ESPHOME
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

    std::string name;
    Color rgb{0};
    HSVColor hsv{0};
    static std::string keys[KEY_COUNT];
    static std::map<std::string, PaletteColor> crayons;
  };

  struct Palette
  {
    enum : uint8_t
    {
      TITLE,
      NOTES,
      COLORS,
      KEY_COUNT,
    };
    std::string title;
    std::string notes;
    std::map<std::string, PaletteColor> colors;
    static std::string keys[KEY_COUNT];
  };
}

#ifndef USE_ESPHOME

namespace YAML
{
  using glow::PaletteColor;

  template <>
  struct convert<PaletteColor>
  {
    static Node encode(const PaletteColor &palette)
    {
      Node node;
      node[PaletteColor::keys[PaletteColor::NAME]] = palette.name;
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
      palette.name = node[PaletteColor::keys[PaletteColor::NAME]].as<std::string>();
      palette.hsv = node[PaletteColor::keys[PaletteColor::HSV]].as<HSVColor>();
      palette.rgb = node[PaletteColor::keys[PaletteColor::RGB]].as<Color>();
      return true;
    }
  };

  using glow::Palette;
  template <>
  struct convert<Palette>
  {
    static Node encode(const Palette &palette)
    {
      Node node;
      node[Palette::keys[Palette::TITLE]] = palette.title;
      node[Palette::keys[Palette::NOTES]] = palette.notes;
      Node list = node[Palette::keys[Palette::COLORS]];
      for (auto item : palette.colors)
      {
        list.push_back(item);
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
        colors.push_back(item.as<PaletteColor>());
      }

      return true;
    }
  };
}
#endif
