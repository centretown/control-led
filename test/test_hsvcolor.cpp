#include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <yaml-cpp/yaml.h>

#include "../src/HSVColor.h"

using namespace glow;

void test_yaml(HSVColor &hsv, std::string input)
{
  YAML::Node node = YAML::convert<HSVColor>::encode(hsv);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl;

  HSVColor hsv_from_node;
  YAML::convert<HSVColor>::decode(node, hsv_from_node);
  int16_t hue_diff = hsv_from_node.hue - hsv.hue;
  int16_t sat_diff = hsv_from_node.saturation - hsv.saturation;
  int16_t val_diff = hsv_from_node.value - hsv.value;

  REQUIRE((hue_diff >= -1 && hue_diff <= 1));
  REQUIRE((sat_diff >= -1 && sat_diff <= 1));
  REQUIRE((val_diff >= -1 && val_diff <= 1));

  YAML::Node input_node = YAML::Load(input);
  HSVColor hsv_from_input;
  YAML::convert<HSVColor>::decode(input_node, hsv_from_input);

  hue_diff = hsv_from_node.hue - hsv_from_input.hue;
  sat_diff = hsv_from_node.saturation - hsv_from_input.saturation;
  val_diff = hsv_from_node.value - hsv_from_input.value;

  REQUIRE((hue_diff >= -1 && hue_diff <= 1));
  REQUIRE((sat_diff >= -1 && sat_diff <= 1));
  REQUIRE((val_diff >= -1 && val_diff <= 1));
}

void test_yaml(Color &color, std::string input)
{
  YAML::Node node = YAML::convert<Color>::encode(color);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl;

  Color color_from_node;
  YAML::convert<Color>::decode(node, color_from_node);
  REQUIRE(color == color_from_node);

  YAML::Node input_node = YAML::Load(input);
  Color color_from_input;
  YAML::convert<Color>::decode(input_node, color_from_input);
  REQUIRE(color == color_from_input);
}

Color rgbColors[] = {
    Color(255, 0, 0),
    Color(127, 0, 0),
    Color(63, 0, 0),

    Color(0, 255, 0),
    Color(0, 127, 0),
    Color(0, 63, 0),

    Color(0, 0, 255),
    Color(0, 0, 127),
    Color(0, 0, 63),

    Color(255, 255, 0),
    Color(255, 127, 0),
    Color(255, 63, 0),
    Color(127, 63, 0),
    Color(63, 31, 0),

    Color(255, 0, 255),
    Color(255, 0, 127),
    Color(255, 0, 63),
    Color(127, 0, 63),
    Color(63, 0, 31),

    Color(255, 255, 0),
    Color(0, 255, 255),
    Color(255, 0, 255),

    Color(55, 10, 11),
    Color(11, 10, 11),
    Color(11, 11, 10),
};

TEST_CASE("HSVColor Basic", "[hsvcolor_basic]")
{
  HSVColor hsv;
  for (int i = 0; i < sizeof(rgbColors) / sizeof(rgbColors[0]); i++)
  {
    Color &color = rgbColors[i];
    hsv.from_rgb(color);
    Color derived = hsv.to_rgb();

    // Verified at RabidTables
    // https://www.rapidtables.com/convert/color/rgb-to-hsv.html

    std::cout << std::endl
              << "\tRGB: (" << (uint16_t)color.red << ", "
              << (uint16_t)color.green << ", "
              << (uint16_t)color.blue << ")"
              << std::endl;

    std::cout << "\trgb: (" << (uint16_t)derived.red << ", "
              << (uint16_t)derived.green << ", "
              << (uint16_t)derived.blue << ")"
              << std::endl;

    std::cout << "\tHSV: (" << hsv.hue << ", "
              << (uint16_t)hsv.saturation << ", "
              << (uint16_t)hsv.value << ")"
              << std::endl;

    REQUIRE(color.raw_32 == derived.raw_32);
  }
}

TEST_CASE("HSVColor YAML", "[hsvcolor_yaml]")
{
  HSVColor hsv(uint16_t(255), 127, 255);
  std::string input =
      "hue: 60\n"
      "saturation: 50\n"
      "value: 100\n";

  test_yaml(hsv, input);

  HSVColor hsv_2(uint16_t(255 + 127), 64, 255);
  input =
      "hue: 90\n"
      "saturation: 25\n"
      "value: 100\n";
  test_yaml(hsv_2, input);

  HSVColor hsv_3(uint16_t(255 + 127), 64, 127);
  input =
      "hue: 90\n"
      "saturation: 25\n"
      "value: 50\n";
  test_yaml(hsv_3, input);
}