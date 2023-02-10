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

TEST_CASE("Frame Basic", "frame_basic")
{
  Frame frame;
  frame.setup(20, 48);

  HSVColor source;
  source.from_color_wheel(float(0), float(100), float(100));
  HSVColor target;
  target.from_color_wheel(float(0), float(50), float(50));
  Chroma chroma;
  chroma.setup(frame.get_length(), source, target, -1);

  Grid grid;
  grid.setup(frame.get_length(), 4, TopLeft, Diagonal);

  Layer layer;
  layer.setup(frame.get_length(), 5, 15, grid, chroma);

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

  std::string file_name = "frame.yaml";
  save_yaml(file_name, frame);

  // test/frame.yaml
  test_yaml_from_file(frame, file_name, check_detail);
}
