#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Layer.h"
#include "../src/Filer.h"
#include "test_yaml.h"
#include "check_layer_detail.h"

using namespace glow;

void check_detail(const Layer &original, const Layer &derived)
{
  check_layer_detail(original, derived);
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
  REQUIRE(chroma.setup(20, source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(20, 5, 15, grid, chroma));
  test_yaml(layer, input, check_detail);

  std::string file_name = "layer.yaml";
  REQUIRE(save_yaml(file_name, layer));

  // test/frame.yaml
  test_yaml_from_file(layer, file_name, check_detail);
}

std::string file_name = "save_palette.yaml";

TEST_CASE("Layer Palette", "layer_palette")
{
  std::string input =
      "length: 20\n"
      "begin: 5\n"
      "end: 15\n"
      "grid:\n"
      "  length: 20\n"
      "  rows: 4\n"
      "  origin: top left\n"
      "  orientation: diagonal\n"
      "chroma:\n"
      "  length: 20\n"
      "  delta: -1\n"
      "  source: apricot\n"
      "  target: beaver\n";

  HSVColor source, target;
  // apricot
  source.from_color_wheel(float(28), float(30), float(99));
  // beaver
  target.from_color_wheel(float(22), float(38), float(57));

  REQUIRE(Chroma::load_palette(file_name));
  Chroma chroma;
  REQUIRE(chroma.setup(20, source, target, 1));

  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(20, 5, 15, grid, chroma));
  test_yaml(layer, input, check_detail);
}
