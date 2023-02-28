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

const std::string layer_name = "layer";

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
      "rows: 4\n"
      "begin: 0\n"
      "end: 100\n"
      "grid:\n"
      "  length: 20\n"
      "  rows: 4\n"
      "  origin: top left\n"
      "  orientation: diagonal\n"
      "chroma:\n"
      "  length: 20\n"
      "  hue_shift: -1\n"
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
  REQUIRE(layer.setup(20, 4, grid, chroma));
  // save_yaml(layer_file(), layer);
  test_yaml(layer, input, check_detail);

  REQUIRE(save_yaml(derived_layer(layer_name), layer));

  test_yaml_from_file(layer, derived_layer(layer_name), check_detail);
}

TEST_CASE("Layer Palette", "layer_palette")
{
  REQUIRE(Chroma::load_palette(palette_file()));

  std::string input =
      "length: 28\n"
      "rows: 4\n"
      "begin: 0\n"
      "end: 100\n"
      "grid:\n"
      "  length: 20\n"
      "  rows: 4\n"
      "  origin: top left\n"
      "  orientation: diagonal\n"
      "chroma:\n"
      "  length: 20\n"
      "  hue_shift: -1\n"
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
  REQUIRE(layer.setup(28, 4, grid, chroma));
  test_yaml(layer, input, check_detail);
  // REQUIRE(save_yaml(custom_layer(layer_name), layer));
  REQUIRE(save_yaml(custom_layer(layer_name), layer));

  Layer layer_custom;
  REQUIRE(load_yaml(custom_layer(layer_name), layer_custom));

  REQUIRE(layer.setup_length(100));
  REQUIRE(layer_custom.setup_length(100));
  check_detail(layer, layer_custom);
}

TEST_CASE("Layer Code", "[layer_make_code]")
{
  REQUIRE(Chroma::load_palette(palette_file()));

  Layer layer;
  REQUIRE(load_yaml(custom_layer(layer_name), layer));
  std::cout << layer.make_code() << '\n';

  Layer layer_generated = {28, 4, {20, 4, 0, 2}, {20, {119, 76, 252}, {0, 0, 255}, -1}, 0, 0, 0, 100};
  check_detail(layer, layer_generated);
}

TEST_CASE("Layer Bounds", "[layer_check_bounds]")
{
  Layer layer;
  Grid grid;
  Chroma chroma;
  layer.setup(20, 4, grid, chroma);
  REQUIRE(0 == layer.get_begin());
  REQUIRE(100 == layer.get_end());
  REQUIRE(0 == layer.get_first());
  REQUIRE(20 == layer.get_last());

  REQUIRE(TopLeft == grid.get_origin());
  REQUIRE(Horizontal == grid.get_orientation());

  layer.setup(20, 4, grid, chroma, 0, 0, 0, 50);
  REQUIRE(0 == layer.get_begin());
  REQUIRE(50 == layer.get_end());
  REQUIRE(0 == layer.get_first());
  REQUIRE(10 == layer.get_last());

  layer.setup(20, 4, grid, chroma, 0, 0, 50);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(100 == layer.get_end());
  REQUIRE(10 == layer.get_first());
  REQUIRE(20 == layer.get_last());

  layer.setup(36, 4, grid, chroma);
  REQUIRE(0 == layer.get_begin());
  REQUIRE(100 == layer.get_end());
  REQUIRE(0 == layer.get_first());
  REQUIRE(36 == layer.get_last());

  layer.setup(36, 4, grid, chroma, 0, 0, 50);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(100 == layer.get_end());
  REQUIRE(18 == layer.get_first());
  REQUIRE(36 == layer.get_last());

  layer.setup(35, 5, grid, chroma, 0, 0, 50);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(100 == layer.get_end());
  REQUIRE(14 == layer.get_first());
  REQUIRE(35 == layer.get_last());

  layer.setup(35, 5, grid, chroma, 0, 0, 50, 75);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(75 == layer.get_end());
  REQUIRE(14 == layer.get_first());
  REQUIRE(21 == layer.get_last());

  layer.setup(35, 5, grid, chroma, 0, 0, 50, 80);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(80 == layer.get_end());
  REQUIRE(14 == layer.get_first());
  REQUIRE(28 == layer.get_last());

  grid.setup(35, 5, 0, Vertical);

  layer.setup(35, 5, grid, chroma, 0, 0, 50);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(100 == layer.get_end());
  REQUIRE(15 == layer.get_first());
  REQUIRE(35 == layer.get_last());

  layer.setup(35, 5, grid, chroma, 0, 0, 50, 75);
  REQUIRE(50 == layer.get_begin());
  REQUIRE(75 == layer.get_end());
  REQUIRE(15 == layer.get_first());
  REQUIRE(25 == layer.get_last());
}
