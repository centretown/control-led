#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "test_yaml.h"
#include "check_chroma_detail.h"
#include "../src/Chroma.h"
#include "../src/Filer.h"

using namespace glow;

const std::string chroma_name = "chroma.yaml";

void check_detail(const Chroma &original, const Chroma &derived)
{
  check_chroma_detail(original, derived);
}

TEST_CASE("Chroma Basic", "chroma_basic")
{
  Chroma chroma;
  HSVColor a, b;
  a.from_color_wheel(float(0), float(100), float(100));
  b.from_color_wheel(float(0), float(50), float(50));
  REQUIRE(chroma.setup(20, a, b, -1));
  std::string input =
      "length: 20\n"
      "delta: -1\n" // out of order
      "source:\n"
      "  hue: 0\n"
      "  saturation: 100\n"
      "  value: 100\n"
      "target:\n"
      "  hue: 0\n"
      "  saturation: 50\n"
      "  value: 50\n";
  test_yaml(chroma, input, check_detail);

  Chroma chroma_length_only;
  REQUIRE(chroma_length_only.setup(20));
  std::string input_length_only =
      "length: 20\n";
  test_yaml(chroma_length_only, input_length_only, check_detail);
}

TEST_CASE("Chroma Palette", "chroma_palette")
{
  REQUIRE(Chroma::load_palette(palette_file()));
  Chroma chroma;
  HSVColor source, target;
  // brick red
  source.from_color_wheel(float(352), float(77), float(78));
  // canary
  target.from_color_wheel(float(60), float(40), float(100));
  REQUIRE(chroma.setup(20, source, target, 1));

  std::string input =
      "length: 20\n"
      "source: brick red\n"
      "target: canary\n"
      "delta: 1\n";

  test_yaml_from_input(chroma, input, check_detail);

  YAML::Node node = YAML::Load(input);
  save_yaml(custom_chroma(chroma_name), node);

  save_yaml(derived_chroma(chroma_name), chroma);
  test_yaml_from_file(chroma, custom_chroma(chroma_name), check_detail);
}