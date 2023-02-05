#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "test_yaml.h"
#include "../src/Chroma.h"
using namespace glow;

void check_detail(Chroma &original, Chroma &derived)
{
  REQUIRE(original.length == derived.length);
  REQUIRE(original.delta == derived.delta);
  REQUIRE(original.hsv_source.raw_32 == derived.hsv_source.raw_32);
  REQUIRE(original.hsv_target.raw_32 == derived.hsv_target.raw_32);
  REQUIRE(original.rgb_source.raw_32 == derived.rgb_source.raw_32);
  REQUIRE(original.rgb_target.raw_32 == derived.rgb_target.raw_32);
  REQUIRE(original.gradient_amount == derived.gradient_amount);
}

TEST_CASE("Chroma Basic", "chroma_basic")
{
  Chroma chroma;
  HSVColor a, b;
  a.from_color_wheel(float(0), float(100), float(100));
  b.from_color_wheel(float(0), float(50), float(50));
  chroma.setup(20, -1, a, b);
  std::string input =
      "length: 20\n"
      "delta: -1\n"
      "source:\n"
      "  hue: 0\n"
      "  saturation: 100\n"
      "  value: 100\n"
      "target:\n"
      "  hue: 0\n"
      "  saturation: 50\n"
      "  value: 50\n";
  test_yaml(chroma, input, check_detail);
}