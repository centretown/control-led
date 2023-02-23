#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "Layer.h"
#include "Filer.h"
#include "test_yaml.h"
#include "check_layer_detail.h"

#include "ansi_stream.h"
#include "HostLight.h"

TEST_CASE("Lights Basic", "layer_basic")
{
  HostLight light;
  REQUIRE(light.setup(40, 4));
  REQUIRE(light.length == 40);
  REQUIRE(light.rows == 4);
  REQUIRE(light.columns == 10);
  Color red(255, 0, 0);
  for (uint16_t i = 0; i < light.length / 2; i++)
  {
    light.put(i, red);
  }

  Color blue(0, 0, 255);
  for (uint16_t i = light.length / 2; i < light.length; i++)
  {
    light.put(i, blue);
  }
}

TEST_CASE("Layer Lights", "layer_lights")
{
  REQUIRE(Chroma::load_palette(palette_file()));
  Layer layer;
  std::string strawberry = "strawberry";
  REQUIRE(load_yaml(custom_layer(strawberry), layer));
  REQUIRE(save_yaml(derived_layer(strawberry), layer));

  ansi_at(0, 0, std::cout);
  ansi_clear_from_cursor(std::cout);
  ansi_hide_cursor(std::cout);

  HostLight light;
  light.setup(layer.get_length(), layer.get_grid().get_rows());
  layer.spin(&light);

  ansi_at(layer.get_grid().get_rows() + 1, 0, std::cout);
  ansi_show_cursor(std::cout);

  YAML::Node node = YAML::convert<Layer>::encode(layer);
  YAML::Emitter out;
  out << node;
  std::cout << '\n'
            << out.c_str() << '\n';
  std::cout << custom_layer(strawberry) << std::endl;
  std::cout << derived_layer(strawberry) << std::endl;
}
