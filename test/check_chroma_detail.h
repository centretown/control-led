#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Chroma.h"
using namespace glow;

void check_chroma_detail(const Chroma &original, const Chroma &derived)
{
  REQUIRE(original.get_length() == derived.get_length());
  REQUIRE(original.get_delta() == derived.get_delta());
  REQUIRE(original.get_hsv_source() == derived.get_hsv_source());
  REQUIRE(original.get_hsv_target() == derived.get_hsv_target());
  REQUIRE(original.get_rgb_source().raw_32 == derived.get_rgb_source().raw_32);
  REQUIRE(original.get_rgb_target().raw_32 == derived.get_rgb_target().raw_32);
  REQUIRE(original.get_gradient_amount() == derived.get_gradient_amount());
}
