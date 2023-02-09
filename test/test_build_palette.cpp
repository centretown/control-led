#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <catch2/catch_all.hpp>

#include <yaml-cpp/yaml.h>
#include "../src/Palette.h"
#include "../src/palette_builder.h"

using namespace glow;

TEST_CASE("Build Palette", "[build_palette]")
{
  std::map<std::string, PaletteColor> &palette = build_palette();

  for (auto item : palette)
  {
    float hue, sat, val;
    item.second.hsv.to_color_wheel(hue, sat, val);
    std::cout << item.second.name << std::endl
              << "\tRGB: "
              << (uint16_t)item.second.rgb.red << ", "
              << (uint16_t)item.second.rgb.green << ", "
              << (uint16_t)item.second.rgb.blue << std::endl
              << "\tHSV: " << (uint16_t)item.second.hsv.hue << ", "
              << (uint16_t)item.second.hsv.saturation << ", "
              << (uint16_t)item.second.hsv.value << std::endl
              << "\tWHL: " << hue << ", "
              << sat << ", "
              << val << std::endl;
  }

  for (auto item : palette)
  {
    YAML::Node node = YAML::convert<PaletteColor>::encode(item.second);
    YAML::Emitter out;
    out << node;
    std::cout << out.c_str() << std::endl;
  }
}
