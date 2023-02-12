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

  REQUIRE(layer.setup(20, 5, 15, grid, chroma));
  REQUIRE(layer1.setup(20, 5, 15, grid, chroma));
  REQUIRE(layer2.setup(20, 5, 15, grid, chroma));

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

  // test_yaml(frame, frame_data, check_detail);
  save_yaml(frame_file(), frame);

  // test/frame.yaml
  // test_yaml_from_file(frame, frame_name, check_detail);
}

// TEST_CASE("Frame Palette", "frame_palette")
// {
//   REQUIRE(Chroma::load_palette(palette_name));
//   YAML::Node node = YAML::Load(frame_data);
//   YAML::Emitter out;
//   out << node;
//   std::cout << out.c_str() << '\n';

//   Frame frame;
//   YAML::convert<Frame>::decode(node, frame);

//   for (auto layer : frame.layers)
//   {
//     auto chroma = layer.get_chroma();
//     std::cout << "chroma " << (uint16_t)chroma.get_length()
//               << " " << chroma.get_delta() << '\n';

//     auto hsv = chroma.get_hsv_source();
//     std::cout << "source " << (uint16_t)hsv.hue << " "
//               << (uint16_t)hsv.saturation << " "
//               << (uint16_t)hsv.value << '\n';
//     hsv = chroma.get_hsv_target();
//     std::cout << "target " << (uint16_t)hsv.hue << " "
//               << (uint16_t)hsv.saturation << " "
//               << (uint16_t)hsv.value << '\n';
//     auto grid = layer.get_grid();
//     std::cout << "grid " << (uint16_t)grid.get_length() << " "
//               << (uint16_t)grid.get_columns() << " "
//               << (uint16_t)grid.get_rows() << '\n';
//   }
// }
