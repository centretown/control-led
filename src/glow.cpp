#include <iostream>
#include <array>
#include <string>
#include <signal.h>
#include <thread>

#include <yaml-cpp/yaml.h>
#include <nlohmann/json.hpp>
#include <cxxopts.hpp>

#include "GlowConfig.h"

#include "Palette.h"
#include "Frame.h"
#include "Filer.h"
#include "DisplayANSI.h"
#include "HostLight.h"

using namespace glow;

const std::array<std::string, 6> search_colors = {
    "sunset orange",
    "salmon",
    "antique brass",
    "aquamarine",
    "blue-violet",
    "brick red",
};

void process_args(int argc, char **argv);
void load_palette();
void load_frame(std::string frame_name, Frame &frame);
void display_selected_colors();
void display_summary();
void sigintHandler(int sig_num);
void show_lights();

std::string frame_name;
Frame frame;

int main(int argc, char **argv)
{
  signal(SIGINT, sigintHandler);

  process_args(argc, argv);

  load_palette();
  display_selected_colors();

  load_frame(frame_name, frame);
  show_lights();
  exit(0);
}

void process_args(int argc, char **argv)
{
#ifdef DATA_DIR
  set_data_path(DATA_DIR);
#endif

  cxxopts::Options options("glow", "Glow: light pattern designer");

  options.add_options()                                                                               //
      ("p,path", "Path to data", cxxopts::value<std::string>()->default_value(data_path()))           //
      ("f,frame", "Frame to show", cxxopts::value<std::string>()->default_value("salmon-strawberry")) //
      ("h,help", "Print usage");                                                                      //

  auto selected = options.parse(argc, argv);

  if (selected.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  set_data_path(selected["path"].as<std::string>());
  frame_name = selected["frame"].as<std::string>();

  if (!file_system_exists())
  {
    if (!make_file_system())
    {
      std::cout << "Failed to create file system at " << '"' << data_path() << '"' << ".\n";
      exit(1);
    }
    std::cout << "File system created at " << '"' << data_path() << '"' << ".\n";
    exit(0);
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

void load_frame(std::string frame_name, Frame &frame)
{
  if (load_yaml(custom_frame(frame_name), frame) == false)
  {
    std::cout << "Unable to load " << custom_frame(frame_name) << " !" << '\n';
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

void display_summary()
{
  YAML::Node node_out = YAML::convert<Frame>::encode(frame);
  YAML::Emitter out;
  out << node_out;
  std::cout << out.c_str() << '\n';
}

void sigintHandler(int sig_num)
{
  DisplayANSI::at(12, 0);
  DisplayANSI::show_cursor();
  display_summary();
  exit(0);
};

void show_lights()
{
  DisplayANSI::at(0, 0);
  DisplayANSI::clear_from_cursor();
  DisplayANSI::hide_cursor();

  HostLight light;
  if (light.setup(frame.get_length(), frame.get_rows()) == false)
  {
    std::cout << "Unable setup light. length: " << frame.get_length()
              << " ,rows: " << frame.get_rows() << '\n';
    exit(1);
  }

  for (;;)
  {
    frame.spin(&light);
    std::this_thread::sleep_for(std::chrono::milliseconds(frame.get_interval()));
  }
}
