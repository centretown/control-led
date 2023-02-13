#include <iostream>
#include <array>

#include <yaml-cpp/yaml.h>

#include "GlowConfig.h"

#include "Palette.h"
#include "Frame.h"
#include "Filer.h"
#include "DisplayANSI.h"

using namespace glow;

std::array<std::string, 6> search_colors = {
    "sunset orange",
    "salmon",
    "antique brass",
    "aquamarine",
    "blue-violet",
    "brick red",
};

void process_args(int argc, char **argv)
{
  if (argc > 1)
  {
    set_data_path(argv[1]);
  }

  // std::cout << data_path() << '\n'
  //           << argv[0] << " Version: "
  //           << Glow_VERSION_MAJOR << '.'
  //           << Glow_VERSION_MINOR << '\n';

  std::cout << "data_path: " << data_path() << '\n';
  std::cout << "Palette: " << palette_file() << '\n';
  std::cout << "Frame: " << frame_file() << '\n';

  if (!file_system_exists())
  {
    if (!make_file_system())
    {
      std::cout << "Failed to create file system";
      exit(1);
    }
  }
}

void load_palette()
{
  if (Chroma::load_palette(palette_file()) == false)
  {
    std::cout << "Unable to load " << palette_file() << " !" << '\n';
    exit(1);
  }
}

void load_frame(Frame &frame)
{
  if (load_yaml(frame_symbolic_file(), frame) == false)
  {
    std::cout << "Unable to load " << frame_symbolic_file() << " !" << '\n';
    exit(1);
  }
}

void display_selected_colors()
{
  PaletteColor palette_color;

  for (auto color_name : search_colors)
  {
    if (Chroma::palette.find_color(color_name, palette_color) == false)
    {
      std::cout << color_name << " not found!" << '\n';
      continue;
    }

    HSVColor hsv_target = Chroma::palette.lookup(color_name);
    std::cout << "hsv" << (uint16_t)hsv_target.hue << ", "
              << (uint16_t)hsv_target.saturation << ", "
              << (uint16_t)hsv_target.value << '\n';

    float hue{}, saturation{}, value{};
    hsv_target.to_color_wheel(hue, saturation, value);
    std::cout << "hsv" << hue << ", "
              << saturation << ", "
              << value << '\n';

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

  load_palette();
  display_selected_colors();

  Frame frame;
  load_frame(frame);

  YAML::Node node_out = YAML::convert<Frame>::encode(frame);
  YAML::Emitter out;
  out << node_out;
  std::cout << out.c_str() << '\n';

  exit(0);
}