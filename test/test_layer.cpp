#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Layer.h"

using namespace glow;

void test_yaml(Layer &layer, std::string input)
{
  YAML::Node node = YAML::convert<Layer>::encode(layer);
  Layer layer_from_node;
  YAML::convert<Layer>::decode(node, layer_from_node);

  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl
            << std::endl;

  node = YAML::convert<Layer>::encode(layer_from_node);
  YAML::Emitter out_a;
  out_a << node;
  std::cout << out_a.c_str() << std::endl
            << std::endl;

  // REQUIRE(layer == layer_from_node);
  // YAML::Node input_node = YAML::Load(input);
  // Layer layer_from_input;
  // YAML::convert<Layer>::decode(input_node, layer_from_input);

  // YAML::Emitter out_b;
  // out_b << input_node;
  // std::cout << out_b.c_str() << std::endl;

  // REQUIRE(layer == layer_from_input);
}

TEST_CASE("Layer Basic", "layer_basic")
{
  std::string input = "";
  Chroma chroma;
  chroma.setup(20, -1,
               HSVColor(float(0), float(100), float(100)),
               HSVColor(float(0), float(50), float(50)));

  Grid grid;
  grid.setup(20, 4, TopLeft, Diagonal);

  Layer layer;
  layer.setup(20, 5, 15, grid, chroma);
  test_yaml(layer, input);
}
