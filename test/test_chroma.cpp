#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Chroma.h"

using namespace glow;

void test_yaml(Chroma &chroma, std::string input)
{
  YAML::Node node = YAML::convert<Chroma>::encode(chroma);
  Chroma chroma_from_node;
  YAML::convert<Chroma>::decode(node, chroma_from_node);

  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl
            << std::endl;

  node = YAML::convert<Chroma>::encode(chroma_from_node);
  YAML::Emitter out_a;
  out_a << node;
  std::cout << out_a.c_str() << std::endl
            << std::endl;

  // REQUIRE(chroma == chroma_from_node);
  YAML::Node input_node = YAML::Load(input);
  Chroma chroma_from_input;
  YAML::convert<Chroma>::decode(input_node, chroma_from_input);

  YAML::Emitter out_b;
  out_b << input_node;
  std::cout << out_b.c_str() << std::endl;

  // REQUIRE(chroma == chroma_from_input);
}

TEST_CASE("Chroma Basic", "chroma_basic")
{
  Chroma chroma;
  chroma.setup(20, -1,
               HSVColor(float(0), float(100), float(100)),
               HSVColor(float(0), float(50), float(50)));
  std::string input =
      "length: 20\n"
      "delta: -1\n"
      "source:\n"
      "  hue: 0\n"
      "  saturation: 100\n"
      "  value: 100\n"
      "target:\n"
      "  hue: 0\n"
      "  saturation: 50\n"
      "  value: 50\n";
  test_yaml(chroma, input);
}