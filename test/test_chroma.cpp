#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "test_yaml.h"
#include "check_chroma_detail.h"
#include "Chroma.h"
#include "Filer.h"

using namespace glow;

const std::string chroma_name = "chroma";

void check_detail(const Chroma &original, const Chroma &derived)
{
  check_chroma_detail(original, derived);
}
void show_chroma(Chroma &chroma)
{
  auto hsv_source = chroma.get_hsv_source();
  auto hsv_target = chroma.get_hsv_target();
  auto rgb_source = chroma.get_rgb_source();
  auto rgb_target = chroma.get_rgb_target();
  std::cout
      << "SOURCE: (" << hsv_source.hue << ", "
      << (uint16_t)hsv_source.saturation << ", "
      << (uint16_t)hsv_source.value << ")"
      << "(" << (uint16_t)rgb_source.red << ", "
      << (uint16_t)rgb_source.green << ", "
      << (uint16_t)rgb_source.blue << ")"
      << '\n';
  std::cout
      << "TARGET: (" << hsv_target.hue << ", "
      << (uint16_t)hsv_target.saturation << ", "
      << (uint16_t)hsv_target.value << ")"
      << "(" << (uint16_t)rgb_target.red << ", "
      << (uint16_t)rgb_target.green << ", "
      << (uint16_t)rgb_target.blue << ")"
      << '\n';
}

TEST_CASE("Chroma Basic", "chroma_basic")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif
  Chroma chroma;
  HSVColor a, b;
  a.from_color_wheel(float(0), float(100), float(100));
  b.from_color_wheel(float(0), float(50), float(50));
  REQUIRE(chroma.setup(20, a, b, -1));
  std::string input =
      "length: 20\n"
      "hue_shift: -1\n" // out of order
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
  REQUIRE(chroma_length_only.setup_length(20));
  std::string input_length_only =
      "length: 20\n";

  test_yaml(chroma_length_only, input_length_only, check_detail);
}

TEST_CASE("Chroma Palette", "chroma_palette")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif
  REQUIRE(Chroma::load_palette(palette_file()));
  Chroma chroma;
  HSVColor source, target;
  // brick red
  source.from_color_wheel(float(352), float(77), float(78));
  // canary
  target.from_color_wheel(float(60), float(40), float(100));
  REQUIRE(chroma.setup(20, source, target, 5));

  std::string input =
      "length: 20\n"
      "source: brick red\n"
      "target: canary\n"
      "hue_shift: 5\n";

  test_yaml_from_input(chroma, input, check_detail);

  YAML::Node node = YAML::Load(input);
  save_yaml(custom_chroma(chroma_name), node);

  save_yaml(derived_chroma(chroma_name), chroma);
  test_yaml_from_file(chroma, custom_chroma(chroma_name), check_detail);
}

TEST_CASE("Chroma Operations", "chroma_operations")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif
  REQUIRE(Chroma::load_palette(palette_file()));
  Chroma chroma;
  REQUIRE(load_yaml(custom_chroma(chroma_name), chroma));

  chroma.set_hue_shift(1);
  show_chroma(chroma);
  Chroma backup = chroma;

  for (auto i = 0; i < 10; i++)
  {
    chroma.update();
    show_chroma(chroma);
    // show_chroma(backup);
    // REQUIRE(chroma.get_hsv_source().hue ==
    //         backup.get_hsv_source().hue + i);
    // REQUIRE(chroma.get_hsv_target().hue ==
    //         backup.get_hsv_target().hue + i);
  }
}

TEST_CASE("Chroma Code", "[chroma_make_code]")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif
  Chroma chroma;
  HSVColor source, target;
  // brick red
  source.from_color_wheel(float(352), float(77), float(78));
  // canary
  target.from_color_wheel(float(60), float(40), float(100));
  REQUIRE(chroma.setup(20, source, target, 5));

  std::cout << chroma.make_code() << '\n';
}

TEST_CASE("Chroma Colors", "chroma_colors")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif
  REQUIRE(Chroma::load_palette(palette_file()));

  std::initializer_list<HSVColor> p_colors = {
      {790, 91, 232},   // aquamarine
      {187, 73, 249},   // banana mania
      {1496, 196, 198}, // brick red
      {255, 102, 255},  // canary
  };

  Chroma chroma(36, p_colors, 2);

  REQUIRE(36 == chroma.get_length());
  REQUIRE(2 == chroma.get_hue_shift());
  REQUIRE(4 == chroma.colors.size());

  auto first = p_colors.begin();
  for (auto &color : chroma.colors)
  {
    REQUIRE(first->hue == color.hue);
    REQUIRE(first->saturation == color.saturation);
    REQUIRE(first->value == color.value);
    first++;
  }

  std::string input =
      "length: 36\n"
      "colors: \n"
      "  - hue: 186\n"
      "    saturation: 36\n"
      "    value: 91\n"
      "  - hue: 44\n"
      "    saturation: 29\n"
      "    value: 98\n"
      "  - hue: 352\n"
      "    saturation: 77\n"
      "    value: 78\n"
      "  - hue: 60\n"
      "    saturation: 40\n"
      "    value: 100\n"
      "hue_shift: 2\n";

  test_yaml_from_input(chroma, input, check_detail);

  std::string input_using_palette =
      "length: 36\n"
      "colors: \n"
      "  - aquamarine\n"
      "  - banana mania\n"
      "  - brick red\n"
      "  - canary\n"
      "hue_shift: 2\n";

  test_yaml_from_input(chroma, input_using_palette, check_detail);
}
