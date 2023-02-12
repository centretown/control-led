#define CATCH_CONFIG_MAIN
#include <iostream>
#include <fstream>

#include <string>
#include <catch2/catch_all.hpp>

#include <yaml-cpp/yaml.h>
#include "Filer.h"
#include "../src/Palette.h"
#include "../src/palette_builder.h"

#include "test_yaml.h"
#include "check_palette_detail.h"

#include "../src/DisplayANSI.h"

using namespace glow;

void check_detail(const Palette &original, const Palette &derived)
{
  check_palette_detail(original, derived);
}


#ifdef BUILD_PALETTE
const std::string test_file_name = "build_palette.yaml";
TEST_CASE("Build Palette", "[build_palette]")
{
  Palette palette;
  palette.title = "Crayola 2023";
  palette.notes = "standard color set 2023";
  palette.colors = build_palette();

  test_yaml_from_struct(palette, check_detail);

  YAML::Node node = YAML::convert<Palette>::encode(palette);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << '\n';

  std::fstream fs;
  fs.open(test_file_name, std::ios_base::out);
  REQUIRE(fs.good());
  fs << out.c_str();
  fs.close();

  Palette from_node;
  YAML::convert<Palette>::decode(node, from_node);

  test_yaml_from_file(palette, test_file_name, check_detail);
}
#endif

const std::string save_file_name = "save_palette.yaml";

TEST_CASE("Build Palette From File", "[build_palette_from_file]")
{
  Palette palette;
  REQUIRE(load_yaml(palette_file(), palette));
  DisplayANSI display;

  for (auto item : palette.colors)
  {
    YAML::Node node = YAML::convert<PaletteColor>::encode(item.second);
    YAML::Emitter out;
    out << node;
    display.print_line(out.c_str(), item.second.rgb);
  }

  REQUIRE(save_yaml(save_file_name, palette));
  test_yaml_from_file(palette, save_file_name, check_detail);
}
