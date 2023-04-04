#include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <yaml-cpp/yaml.h>

#include "HSVColor.h"

using namespace glow;

void test_yaml(HSVColor &hsv, std::string input)
{
  YAML::Node node = YAML::convert<HSVColor>::encode(hsv);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << '\n';

  HSVColor hsv_from_node;
  YAML::convert<HSVColor>::decode(node, hsv_from_node);
  YAML::Emitter out_a;
  YAML::Node node_a = YAML::convert<HSVColor>::encode(hsv_from_node);
  out_a << node_a;
  std::cout << out.c_str() << '\n';

  std::cout << "\tHSV: (" << hsv.hue << ", "
            << (uint16_t)hsv.saturation << ", "
            << (uint16_t)hsv.value << ")"
            << '\n';

  std::cout << "\tHSV: (" << hsv_from_node.hue << ", "
            << (uint16_t)hsv_from_node.saturation << ", "
            << (uint16_t)hsv_from_node.value << ")"
            << '\n';

  YAML::Node input_node = YAML::Load(input);
  HSVColor hsv_from_input;
  YAML::convert<HSVColor>::decode(input_node, hsv_from_input);

}

void test_yaml(Color &color, std::string input)
{
  YAML::Node node = YAML::convert<Color>::encode(color);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << '\n';

  Color color_from_node;
  YAML::convert<Color>::decode(node, color_from_node);
  REQUIRE(color.red == color_from_node.red);
  REQUIRE(color.green == color_from_node.green);
  REQUIRE(color.blue == color_from_node.blue);

  YAML::Node input_node = YAML::Load(input);
  Color color_from_input;
  YAML::convert<Color>::decode(input_node, color_from_input);
  REQUIRE(color.red == color_from_input.red);
  REQUIRE(color.green == color_from_input.green);
  REQUIRE(color.blue == color_from_input.blue);
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

    std::cout << '\n'
              << "\tRGB: (" << (uint16_t)color.red << ", "
              << (uint16_t)color.green << ", "
              << (uint16_t)color.blue << ")"
              << '\n';

    std::cout << "\trgb: (" << (uint16_t)derived.red << ", "
              << (uint16_t)derived.green << ", "
              << (uint16_t)derived.blue << ")"
              << '\n';

    std::cout << "\tHSV: (" << hsv.hue << ", "
              << (uint16_t)hsv.saturation << ", "
              << (uint16_t)hsv.value << ")"
              << '\n';

    REQUIRE(color.red == derived.red);
    REQUIRE(color.green == derived.green);
    REQUIRE(color.blue == derived.blue);
  }
}

TEST_CASE("HSVColor YAML", "[hsvcolor_yaml]")
{
  HSVColor hsv;

  hsv.from_color_wheel(60.0, 50.0, 100.0);
  std::string input =
      "hue: 60\n"
      "saturation: 50\n"
      "value: 100\n";

  test_yaml(hsv, input);

  hsv.from_color_wheel(90.0, 25.0, 100.0);
  input =
      "hue: 90\n"
      "saturation: 25\n"
      "value: 100\n";
  test_yaml(hsv, input);

  hsv.from_color_wheel(90.0, 25.0, 50.0);
  input =
      "hue: 90\n"
      "saturation: 25\n"
      "value: 50\n";
  test_yaml(hsv, input);
}

TEST_CASE("HSVColor Code", "[hsvcolor_make_code]")
{
  HSVColor hsv;
  hsv.from_color_wheel(90.0, 25.0, 50.0);
  std::cout << hsv.make_code();
  hsv.from_color_wheel(90.0, 25.0, 100.0);
  std::cout << hsv.make_code();
  hsv.from_color_wheel(60.0, 50.0, 100.0);
  std::cout << hsv.make_code() << '\n';
}

TEST_CASE("HSVColor Gradient", "[hsvcolor_gradient]")
{
  HSVColor base{0, 255, 255};
  HSVColor first{100, 100, 100};

  HSVColor result = base.to_gradient(first, 5, 10);

  std::cout << base.make_code() << '\n';
  std::cout << first.make_code() << '\n';
  std::cout << result.make_code() << '\n';

  result = first.to_gradient(base, 5, 10);
  std::cout << first.make_code() << '\n';
  std::cout << base.make_code() << '\n';
  std::cout << result.make_code() << '\n';
}
