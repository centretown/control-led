#define CATCH_CONFIG_MAIN
#include <list>
#include <map>
#include <iostream>
#include <catch2/catch_all.hpp>
#include <nlohmann/json.hpp>

#include "Filer.h"
#include "../src/RGBColor.h"
#include "../src/Palette.h"

using namespace glow;

void set_color(nlohmann::json &rgb_json, Color rgb)
{
  rgb_json[rgb.keys[Color::RED]] = rgb.red;
  rgb_json[rgb.keys[Color::GREEN]] = rgb.green;
  rgb_json[rgb.keys[Color::BLUE]] = rgb.blue;
}

TEST_CASE("JSON Basic", "json_basic")
{
  nlohmann::json rgb_json;
  Color rgb(255, 127, 0);

  rgb_json[rgb.keys[Color::RED]] = rgb.red;
  rgb_json[rgb.keys[Color::GREEN]] = rgb.green;
  rgb_json[rgb.keys[Color::BLUE]] = rgb.blue;

  for (auto &el : rgb_json.items())
  {
    std::cout << el.key() << " : " << el.value() << "\n";
  }
  std::cout << rgb_json.dump(2) << "\n";
}

TEST_CASE("JSON Palette", "json_palette")
{
  Palette palette;
  REQUIRE(load_yaml(palette_file(), palette));

  nlohmann::json palette_json;

  for (auto palette_color : palette.colors)
  {
    nlohmann::json rgb_json;
    set_color(rgb_json, palette_color.second.rgb);
    std::cout << rgb_json.dump(2) << '\n';
    palette_json[palette_color.first] = palette_json.parse(rgb_json.dump());
  }
  std::cout << palette_json.dump(2) << "\n";
}
