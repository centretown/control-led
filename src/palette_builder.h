#pragma once

#include <map>
#include "HSVColor.h"
#include "Palette.h"

#define BUILD_PALETTE
namespace glow
{
  std::map<std::string, PaletteColor> &build_palette();
} // namespace glow
