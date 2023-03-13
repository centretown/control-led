#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "Chroma.h"
#include "check_hsvcolor_detail.h"
#include "check_rgbcolor_detail.h"

using glow::Chroma;

void check_chroma_detail(const Chroma &original, const Chroma &derived)
{
  REQUIRE(original.get_length() == derived.get_length());
  REQUIRE(original.get_hue_shift() == derived.get_hue_shift());
  // check_hsvcolor_detail(original.get_hsv_source(), derived.get_hsv_source());
  // check_hsvcolor_detail(original.get_hsv_target(), derived.get_hsv_target());
  // check_rgbcolor_detail(original.get_rgb_source(), derived.get_rgb_source());
  // check_rgbcolor_detail(original.get_rgb_target(), derived.get_rgb_target());
  // REQUIRE(original.get_gradient_amount() == derived.get_gradient_amount());

  auto original_iter = original.colors.begin();
  auto derived_iter = derived.colors.begin();
  while (original_iter != original.colors.end())
  {
    check_hsvcolor_detail(*original_iter, *derived_iter);
    original_iter++;
    derived_iter++;
  }
}
