#include <iostream>
#include <array>

#include <yaml-cpp/yaml.h>

#include "GlowConfig.h"

#include "Palette.h"
#include "Filer.h"
#include "DisplayANSI.h"

using namespace glow;
// using namespace YAML;

std::array<std::string, 10> search_colors = {
    "violet (ii)",
    "venetian red",
    "tumbleweed",
    "sunset orange",
    "almond",
    "antique brass",
    "asparagus",
    "beaver",
    "blue-violet",
    "brick red",
};

const std::string file_name_default = "palette.yaml";
std::string file_name = file_name_default;

void process_args(int argc, char **argv)
{
  std::cout << '\n'
            << argv[0] << " Version: "
            << Glow_VERSION_MAJOR << '.'
            << Glow_VERSION_MINOR << '\n';
  if (argc > 1)
  {
    std::cout << argv[1] << '\n';
    file_name = argv[1];
  }
}

void load(Palette &palette)
{
  if (load_yaml(file_name, palette) == false)
  {
    std::cout << "Unable to load " << file_name << " !" << '\n';
    exit(1);
  }
}

void display_selected_colors(Palette &palette)
{
  PaletteColor palette_color;

  for (auto color_name : search_colors)
  {
    if (palette.find_color(color_name, palette_color) == false)
    {
      std::cout << color_name << " not found!" << '\n';
      continue;
    }

    YAML::Node node = YAML::convert<PaletteColor>::encode(palette_color);
    YAML::Emitter out;
    out << node;

    DisplayANSI::print_line(color_name, palette_color.rgb);
    DisplayANSI::print_line(out.c_str(), palette_color.rgb);
  }
}

int main(int argc, char **argv)
{
  process_args(argc, argv);

  Palette palette;
  load(palette);
  display_selected_colors(palette);

  exit(0);
}