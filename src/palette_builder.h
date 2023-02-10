#pragma once

#include <map>
#include <fstream>

#include "HSVColor.h"
#include "Palette.h"

// #define BUILD_PALETTE
namespace glow
{
#ifdef BUILD_PALETTE
  std::map<std::string, PaletteColor> &build_palette();
#endif

} // namespace glow
