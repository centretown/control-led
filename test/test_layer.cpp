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

void set_apricot_beaver(HSVColor &source, HSVColor &target)
{
  // apricot
  source.from_color_wheel(float(28), float(30), float(99));
  // beaver
  target.from_color_wheel(float(22), float(38), float(57));
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
      "  origin: top left\n"
      "  orientation: diagonal\n"
      "chroma:\n"
      "  length: 20\n"
      "  delta: -1\n"
      "  source:\n"
      "    hue: 28\n"
      "    saturation: 30\n"
      "    value: 99\n"
      "  target:\n"
      "    hue: 22\n"
      "    saturation: 38\n"
      "    value: 57\n";

  HSVColor source, target;
  set_apricot_beaver(source, target);

  Chroma chroma;
  REQUIRE(chroma.setup(20, source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(20, 5, 15, grid, chroma));
  // save_yaml(layer_file(), layer);
  test_yaml(layer, input, check_detail);

  REQUIRE(save_yaml(layer_file(), layer));

  test_yaml_from_file(layer, layer_file(), check_detail);
}

TEST_CASE("Layer Palette", "layer_palette")
{
  REQUIRE(Chroma::load_palette(palette_file()));

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
  set_apricot_beaver(source, target);

  Chroma chroma;
  REQUIRE(chroma.setup(20, source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(20, 5, 15, grid, chroma));
  test_yaml(layer, input, check_detail);

  // YAML::Node node = YAML::Load(input);
  // std::cout << layer_file() << '\n';
  // std::cout << layer_symbolic_file() << '\n';

  // save_yaml(layer_symbolic_file(), node);

  save_yaml(layer_file(), layer);
  test_yaml_from_file(layer, layer_symbolic_file(), check_detail);
}
