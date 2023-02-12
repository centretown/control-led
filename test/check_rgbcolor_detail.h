#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/HSVColor.h"
using glow::Color;

void check_rgbcolor_detail(const Color &original, const Color &derived)
{
  REQUIRE(original.red == derived.red);
  REQUIRE(original.green == derived.green);
  REQUIRE(original.blue == derived.blue);
}
