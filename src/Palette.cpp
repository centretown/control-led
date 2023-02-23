#ifndef MICRO_CONTROLLER

#include "Palette.h"

namespace glow
{

  std::string Palette::keys[Palette::KEY_COUNT] = {
      "title",
      "notes",
      "colors",
  };

  bool Palette::find_color(std::string color_name, PaletteColor &found)
  {
    auto item = colors.find(color_name);
    if (item == colors.end())
    {
      return false;
    }

    found = item->second;
    return true;
  }

  void Palette::print_by_hue(uint16_t columns, uint16_t column_width, std::ostream &stream)
  {
    std::map<uint16_t, PaletteColorX> by_hue{};
    auto print_item = [](std::map<uint16_t, glow::PaletteColorX>::iterator &item,
                         uint16_t column_width, std::ostream &stream)
    {
      ansi_print_fixed(column_width, item->second.name, item->second.color.rgb, stream);
    };
    for (auto color : colors)
    {
      auto px = PaletteColorX{color.first, color.second};
      by_hue[color.second.hsv.hue] = px;
    }
    print_x<std::map<uint16_t, glow::PaletteColorX>::iterator>(columns, column_width, by_hue.begin(), by_hue.end(), stream, print_item);
  }

  void Palette::print(uint16_t columns, uint16_t column_width, std::ostream &stream)
  {
    // std::map<std::string, glow::PaletteColor>::iterator
    auto print_item = [](std::map<std::string, glow::PaletteColor>::iterator &item,
                         uint16_t column_width, std::ostream &stream)
    {
      ansi_print_fixed(column_width, item->first, item->second.rgb, stream);
    };

    print_x<std::map<std::string, glow::PaletteColor>::iterator>(columns, column_width, colors.begin(), colors.end(), stream, print_item);
    // std::vector<std::map<std::string, glow::PaletteColor>::iterator> items;
    // auto print_items = [&]()
    // {
    //   for (auto item : items)
    //   {
    //     ansi_print_fixed(column_width, item->first, item->second.rgb, stream);
    //   }
    //   stream << '\n';
    // };

    // for (auto item = colors.begin(); item != colors.end(); item++)
    // {
    //   items.push_back(item);
    //   if (items.size() == columns)
    //   {
    //     print_items();
    //     items.clear();
    //   }
    // }
  }
}

#endif // MICRO_CONTROLLER
