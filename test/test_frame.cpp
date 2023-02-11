#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>
#include <array>

#include "../src/Frame.h"
#include "../src/Filer.h"

using namespace glow;

#include "test_yaml.h"
#include "test_frame.yml.h"
#include "check_frame_detail.h"

void check_detail(const Frame &original, const Frame &derived)
{
  check_frame_detail(original, derived);
}

std::string palette_name = "../../palette.yaml";
std::string frame_name = "../../frame.yaml";
std::string palette_frame_name = "../../palette_frame.yaml";

TEST_CASE("Frame Basic", "frame_basic")
{
  Frame frame;
  frame.setup(20, 48);

  HSVColor source;
  source.from_color_wheel(float(0), float(100), float(100));
  HSVColor target;
  target.from_color_wheel(float(0), float(50), float(50));

  Chroma chroma;
  REQUIRE(chroma.setup(frame.get_length(), source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(frame.get_length(), 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(frame.get_length(), 5, 15, grid, chroma));

  std::array<Layer, 5> layers = {
      layer,
      layer,
      layer,
      layer,
      layer,
  };

  layers[4].set_length(16);

  for (const auto &layer : layers)
  {
    frame.push_back(layer);
  }
  test_yaml(frame, frame_data, check_detail);

  save_yaml(frame_name, frame);

  // test/frame.yaml
  test_yaml_from_file(frame, frame_name, check_detail);
}

TEST_CASE("Frame Palette", "frame_palette")
{
  Frame frame;
  frame.setup(20, 48);

  HSVColor source, target;
  // aquamarine
  source.from_color_wheel(float(186), float(36), float(91));
  // salmon
  target.from_color_wheel(float(350), float(43), float(100));

  REQUIRE(Chroma::load_palette(palette_name));
  Chroma chroma;
  REQUIRE(chroma.setup(frame.get_length(), source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(frame.get_length(), 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(frame.get_length(), 5, 15, grid, chroma));

  std::array<Layer, 5> layers = {
      layer,
      layer,
      layer,
      layer,
      layer,
  };

  layers[4].set_length(16);

  for (const auto &layer : layers)
  {
    frame.push_back(layer);
  }
  // test/frame.yaml
  test_yaml_from_file(frame, palette_frame_name, check_detail);
}
