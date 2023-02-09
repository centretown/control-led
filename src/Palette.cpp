#include "Palette.h"

namespace glow
{
  std::string PaletteColor::keys[PaletteColor::KEY_COUNT] = {
      "name",
      "rgb",
      "hsv",
  };

  std::string Palette::keys[Palette::KEY_COUNT] = {
      "name",
      "rgb",
      "hsv",
  };
}