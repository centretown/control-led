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

}