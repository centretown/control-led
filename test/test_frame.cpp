#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>
#include <array>

#include "Frame.h"
#include "Filer.h"

using namespace glow;

#include "test_yaml.h"
#include "test_frame.yml.h"
#include "check_frame_detail.h"

const std::string frame_name = "frame";

void check_detail(const Frame &original, const Frame &derived)
{
  check_frame_detail(original, derived);
}

TEST_CASE("Frame Basic", "frame_basic")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  Frame frame;
  frame.setup(20, 4, 48);

  HSVColor source, target;
  // apricot
  source.from_color_wheel(float(28), float(30), float(99));
  // beaver
  target.from_color_wheel(float(22), float(38), float(57));

  Chroma chroma;
  REQUIRE(chroma.setup(frame.get_length(), source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(frame.get_length(), 4, TopLeft, Diagonal));

  Layer layer, layer1, layer2;

  REQUIRE(layer.setup(20, 4, grid, chroma));
  REQUIRE(layer1.setup(20, 4, grid, chroma));
  REQUIRE(layer2.setup(20, 4, grid, chroma));

  float hue{}, saturation{}, value{};

  auto c = layer.get_chroma();
  c.get_hsv_source().to_color_wheel(hue, saturation, value);
  std::cout << "hsv " << hue << " " << saturation << " " << value << '\n';

  chroma.get_hsv_source().to_color_wheel(hue, saturation, value);
  std::cout << "hsv " << hue << " " << saturation << " " << value << '\n';

  frame.push_back(layer);
  frame.push_back(layer1);
  frame.push_back(layer2);
  REQUIRE(frame.layers.size() == 3);
  frame.setup();

  save_yaml(derived_frame(frame_name), frame);
  test_yaml_from_file(frame, derived_frame(frame_name), check_detail);
}

TEST_CASE("Frame Custom", "frame_custom")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  REQUIRE(Chroma::load_palette(palette_file()));
  Frame custom;

  REQUIRE(load_yaml(custom_frame(frame_name), custom));
  REQUIRE(save_yaml(derived_frame(frame_name), custom));

  Frame derived;
  REQUIRE(load_yaml(derived_frame(frame_name), derived));
  check_detail(custom, derived);
}

TEST_CASE("Frame Salmon-Strawberry", "frame_salmon_strawberry")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  REQUIRE(Chroma::load_palette(palette_file()));
  Frame custom;

  std::string salmon_name = "salmon-strawberry";

  REQUIRE(load_yaml(custom_frame(salmon_name), custom));
  REQUIRE(save_yaml(derived_frame(salmon_name), custom));

  Frame derived;
  REQUIRE(load_yaml(derived_frame(salmon_name), derived));
  check_detail(custom, derived);
}

TEST_CASE("Frame Code", "[frame_make_code]")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  REQUIRE(Chroma::load_palette(palette_file()));
  Frame frame;
  REQUIRE(load_yaml(custom_frame(frame_name), frame));
  std::cout << frame.make_code() << '\n';

  Frame frame_generated = //
      {20, 4, 48,         //
       {
           {20, 4, {20, 4, 0, 1}, {20, {790, 91, 232}, {1487, 109, 255}, -1}, 0, 0, 5, 15},
           {20, 4, {20, 4, 0, 1}, {20, {1402, 204, 255}, {807, 124, 234}, -1}, 0, 5, 5, 15},
       }};

  check_detail(frame, frame_generated);

  Frame frame_list[] = {
      {20, 4, 48, //
       {
           {20, 15, {20, 4, 0, 1}, {20, {790, 91, 232}, {1487, 109, 255}, -1}, 0, 0, 4, 5},
           {20, 15, {20, 4, 0, 1}, {20, {1402, 204, 255}, {807, 124, 234}, -1}, 0, 5, 4, 5},
       }},
      {20, 4, 48, //
       {
           {20, 4, {20, 4, 0, 1}, {20, {790, 91, 232}, {1487, 109, 255}, -1}, 0, 0, 5, 15},
           {20, 4, {20, 4, 0, 1}, {20, {1402, 204, 255}, {807, 124, 234}, -1}, 0, 5, 5, 15},
       }},
  };
}

TEST_CASE("Frame Copy", "[frame_copy]")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  REQUIRE(Chroma::load_palette(palette_file()));
  Frame frame;
  REQUIRE(load_yaml(custom_frame(frame_name), frame));

  Frame copy;
  copy.copy(frame);
  check_detail(frame, copy);
}
