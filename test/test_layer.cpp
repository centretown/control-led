#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Layer.h"
#include "test_yaml.h"

using namespace glow;

void check_detail(Layer &original, Layer &derived)
{
  REQUIRE(original.length == derived.length);
  REQUIRE(original.begin == derived.begin);
  REQUIRE(original.end == derived.end);
  REQUIRE(original.length == derived.length);
  REQUIRE(original.length == derived.length);
  REQUIRE(original.grid.rows == derived.grid.rows);
  REQUIRE(original.grid.origin == derived.grid.origin);
  REQUIRE(original.grid.orientation == derived.grid.orientation);
  REQUIRE(original.grid.pivot.first == derived.grid.pivot.first);
  REQUIRE(original.grid.pivot.offset == derived.grid.pivot.offset);
  REQUIRE(original.grid.pivot.last == derived.grid.pivot.last);
  REQUIRE(original.chroma.delta == derived.chroma.delta);
  REQUIRE(original.chroma.hsv_source.raw_32 == derived.chroma.hsv_source.raw_32);
  REQUIRE(original.chroma.hsv_target.raw_32 == derived.chroma.hsv_target.raw_32);
  REQUIRE(original.chroma.rgb_source.raw_32 == derived.chroma.rgb_source.raw_32);
  REQUIRE(original.chroma.rgb_target.raw_32 == derived.chroma.rgb_target.raw_32);
  REQUIRE(original.chroma.gradient_amount == derived.chroma.gradient_amount);
}

TEST_CASE("Layer Basic", "layer_basic")
{
  std::string input =
      "length: 20\n"
      "begin: 5\n"
      "end: 15\n"
      "grid:\n"
      "  length: 20\n"
      "  rows: 4\n"
      "  origin: 0\n"
      "  orientation: 2\n"
      "chroma:\n"
      "  length: 20\n"
      "  delta: -1\n"
      "  source:\n"
      "    hue: 0\n"
      "    saturation: 100\n"
      "    value: 100\n"
      "  target:\n"
      "    hue: 0\n"
      "    saturation: 50\n"
      "    value: 50\n";

  HSVColor source;
  source.from_color_wheel(float(0), float(100), float(100));
  HSVColor target;
  target.from_color_wheel(float(0), float(50), float(50));
  Chroma chroma;
  chroma.setup(20, -1, source, target);

  Grid grid;
  grid.setup(20, 4, TopLeft, Diagonal);

  Layer layer;
  layer.setup(20, 5, 15, grid, chroma);
  test_yaml(layer, input, check_detail);
}
