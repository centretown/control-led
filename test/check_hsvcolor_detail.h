#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "HSVColor.h"
using glow::HSVColor;

void check_hsvcolor_detail(const HSVColor &original, const HSVColor &derived)
{
  REQUIRE((uint16_t)original.hue == (uint16_t)derived.hue);
  REQUIRE((uint16_t)original.saturation == (uint16_t)derived.saturation);
  REQUIRE((uint16_t)original.value == (uint16_t)derived.value);
}
