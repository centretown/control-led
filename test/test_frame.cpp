#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>
#include <array>

#include "test_yaml.h"
#include "../src/Frame.h"
#include "test_frame.yml.h"

using namespace glow;

void check_detail(Frame &original, Frame &derived)
{
  REQUIRE(original.length == derived.length);
  REQUIRE(original.interval == derived.interval);
  REQUIRE(original.layers.size() == derived.layers.size());

  auto iter_original = original.layers.begin();
  auto iter_derived = derived.layers.begin();
  while (iter_original != original.layers.end())
  {
    auto layer_original = *iter_original;
    auto layer_derived = *iter_derived;

    REQUIRE(layer_original.length == layer_derived.length);
    REQUIRE(layer_original.begin == layer_derived.begin);
    REQUIRE(layer_original.end == layer_derived.end);
    REQUIRE(layer_original.length == layer_derived.length);
    REQUIRE(layer_original.length == layer_derived.length);
    REQUIRE(layer_original.grid.rows == layer_derived.grid.rows);
    REQUIRE(layer_original.grid.origin == layer_derived.grid.origin);
    REQUIRE(layer_original.grid.orientation == layer_derived.grid.orientation);
    REQUIRE(layer_original.grid.pivot.first == layer_derived.grid.pivot.first);
    REQUIRE(layer_original.grid.pivot.offset == layer_derived.grid.pivot.offset);
    REQUIRE(layer_original.grid.pivot.last == layer_derived.grid.pivot.last);
    REQUIRE(layer_original.chroma.delta == layer_derived.chroma.delta);
    REQUIRE(layer_original.chroma.hsv_source.raw_32 == layer_derived.chroma.hsv_source.raw_32);
    REQUIRE(layer_original.chroma.hsv_target.raw_32 == layer_derived.chroma.hsv_target.raw_32);
    REQUIRE(layer_original.chroma.rgb_source.raw_32 == layer_derived.chroma.rgb_source.raw_32);
    REQUIRE(layer_original.chroma.rgb_target.raw_32 == layer_derived.chroma.rgb_target.raw_32);
    REQUIRE(layer_original.chroma.gradient_amount == layer_derived.chroma.gradient_amount);

    ++iter_original;
    ++iter_derived;
  }
}

TEST_CASE("Frame Basic", "frame_basic")
{
  Frame frame;
  frame.length = 20;
  frame.interval = 48;

  HSVColor source;
  source.from_color_wheel(float(0), float(100), float(100));
  HSVColor target;
  target.from_color_wheel(float(0), float(50), float(50));
  Chroma chroma;
  chroma.setup(frame.length, -1, source, target);

  Grid grid;
  grid.setup(frame.length, 4, TopLeft, Diagonal);

  Layer layer;
  layer.setup(frame.length, 5, 15, grid, chroma);

  std::array<Layer, 5> layers = {
      layer,
      layer,
      layer,
      layer,
      layer,
  };

  layers[4].length = 16;
  layers[4].setup();
  for (const auto &layer : layers)
  {
    frame.layers.push_back(layer);
  }
  test_yaml(frame, frame_data, check_detail);
}
