#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "Palette.h"
#include "check_hsvcolor_detail.h"
#include "check_rgbcolor_detail.h"

using glow::Palette;
using glow::PaletteColor;

void check_palette_detail(const Palette &original, const Palette &derived)
{
  REQUIRE(original.title == derived.title);
  REQUIRE(original.title == derived.title);
  REQUIRE(original.colors.size() == derived.colors.size());

  auto iter_original = original.colors.begin();
  auto iter_derived = derived.colors.begin();
  while (iter_original != original.colors.end())
  {
    check_hsvcolor_detail(iter_original->second.hsv,
                          iter_derived->second.hsv);

    ++iter_original;
    ++iter_derived;
  }
}
