#define CATCH_CONFIG_MAIN
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <catch2/catch_all.hpp>
#include <nlohmann/json.hpp>

#include "Filer.h"
#include "RGBColor.h"
#include "PaletteColor.h"
#include "Palette.h"

using namespace glow;

void set_color(nlohmann::json &color_json, std::string name, PaletteColor &palette_color)
{
  Color rgb = palette_color.rgb;
  nlohmann::json rgb_json;
  rgb_json[Color::keys[Color::RED]] = rgb.red;
  rgb_json[Color::keys[Color::GREEN]] = rgb.green;
  rgb_json[Color::keys[Color::BLUE]] = rgb.blue;
  color_json[name] = rgb_json;
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
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  Palette palette;
  REQUIRE(load_yaml(palette_file(), palette));

  nlohmann::json palette_json, colors;
  palette_json[palette.keys[Palette::TITLE]] = palette.title;
  palette_json[palette.keys[Palette::NOTES]] = palette.notes;

  for (auto palette_color : palette.colors)
  {
    nlohmann::json palette_color_json;
    set_color(palette_color_json,
              palette_color.first, palette_color.second);
    colors.push_back(palette_color_json);
  }

  palette_json[palette.keys[Palette::COLORS]] = colors;
  // std::cout << palette_json.dump(2) << "\n";
  std::fstream json_stream;

  json_stream.open("palette.json",std::ios_base::out);
  REQUIRE(json_stream.good());
  json_stream << palette_json.dump(2) << '\n';
  json_stream.close();
}
