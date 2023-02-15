#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Layer.h"
#include "../src/Filer.h"
#include "test_yaml.h"
#include "check_layer_detail.h"

#include "HostLight.h"

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
  target.from_color_wheel(float(0), float(0), float(100));
}

TEST_CASE("Layer Basic", "layer_basic")
{
  std::string input =
      "length: 20\n"
      "begin: 0\n"
      "end: 0\n"
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
      "    hue: 0\n"
      "    saturation: 0\n"
      "    value: 100\n";

  HSVColor source, target;
  set_apricot_beaver(source, target);

  Chroma chroma;
  REQUIRE(chroma.setup(20, source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(20, 0, 0, grid, chroma));
  // save_yaml(layer_file(), layer);
  test_yaml(layer, input, check_detail);

  REQUIRE(save_yaml(layer_file(), layer));

  test_yaml_from_file(layer, layer_file(), check_detail);
}

TEST_CASE("Layer Palette", "layer_palette")
{
  REQUIRE(Chroma::load_palette(palette_file()));

  std::string input =
      "length: 28\n"
      "begin: 0\n"
      "end: 0\n"
      "grid:\n"
      "  length: 20\n"
      "  rows: 4\n"
      "  origin: top left\n"
      "  orientation: diagonal\n"
      "chroma:\n"
      "  length: 20\n"
      "  delta: -1\n"
      "  source: apricot\n"
      "  target:\n"
      "    hue: 0\n"
      "    saturation: 0\n"
      "    value: 100\n";

  HSVColor source, target;
  set_apricot_beaver(source, target);

  Chroma chroma;
  REQUIRE(chroma.setup(20, source, target, -1));

  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));

  Layer layer;
  REQUIRE(layer.setup(28, 0, 0, grid, chroma));
  test_yaml(layer, input, check_detail);
  REQUIRE(save_yaml(layer_file(), layer));

  Layer layer_symbolic;
  REQUIRE(load_yaml(layer_symbolic_file(), layer_symbolic));
  REQUIRE(layer.setup_length(100));
  REQUIRE(layer_symbolic.setup_length(100));
  check_detail(layer, layer_symbolic);
}
