#include <iostream>
#include <sstream>
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
#include "ansi_stream.h"
#include "HostLight.h"

using namespace glow;

void process_args(int argc, char **argv);
void load_palette();
void load_frame(std::string frame_name, Frame &frame);
void display_colors();
void display_summary();
void sigintHandler(int sig_num);
void show_lights();

struct Selected
{
  std::string frame_name;
  Frame frame;
  uint16_t length = 36;
  uint16_t rows = 4;
  uint32_t interval = 48;
  bool catalog = false;
} selected;

cxxopts::ParseResult selections;

int main(int argc, char **argv)
{
  signal(SIGINT, sigintHandler);

  process_args(argc, argv);
  load_palette();
  
  if (selections.count("palette"))
  {
    display_colors();
    exit(0);
  }

  selected.frame_name = selections["show"].as<std::string>();
  selected.length = selections["length"].as<uint16_t>();
  selected.rows = selections["rows"].as<uint16_t>();
  selected.interval = selections["interval"].as<uint32_t>();

  load_frame(selected.frame_name, selected.frame);
  show_lights();
  exit(0);
}

void process_args(int argc, char **argv)
{
  cxxopts::Options options("glow", "Glow: create and animate led light strips");

  options.add_options()                                           //
      ("d,data", "Data location",                                 //
       cxxopts::value<std::string>()->default_value(data_path())) //
      ("s,show", "Show frame by name",                            //
       cxxopts::value<std::string>()->default_value("glow"))      //
      ("l,length", "Length of led strip",                         //
       cxxopts::value<uint16_t>()->default_value("36"))           //
      ("r,rows", "Rows in led strip",                             //
       cxxopts::value<uint16_t>()->default_value("4"))            //
      ("i,interval", "Interval in ms",                            //
       cxxopts::value<uint32_t>()->default_value("48"))           //
      ("c,catalog", "Print catalog")                              //
      ("a,add", "Add to catalog",                                 //
       cxxopts::value<std::string>()->default_value(""))          //
      ("b,build", "Build catalog")                                //
      ("p,palette", "Print current palette")                      //
      ("h,help", "Print usage");                                  //

  selections = options.parse(argc, argv);

  if (selections.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  set_data_path(selections["data"].as<std::string>());

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

void display_colors()
{
  // Chroma::palette.print(5, 26, std::cout);
  Chroma::palette.print_by_hue(5, 26, std::cout);
}

void display_summary()
{
  YAML::Node node_out = YAML::convert<Frame>::encode(selected.frame);
  YAML::Emitter out;
  out << node_out;
  std::cout << out.c_str() << '\n';
  display_colors();
}

void sigintHandler(int sig_num)
{
  ansi_at(12, 0, std::cout);
  ansi_show_cursor(std::cout);
  display_summary();
  exit(0);
};

void show_lights()
{
  ansi_at(0, 0, std::cout);
  ansi_clear_from_cursor(std::cout);
  ansi_hide_cursor(std::cout);

  HostLight light;
  if (light.setup(selected.length, selected.rows) == false)
  {
    std::cout << "Unable setup light. length: " << selected.frame.get_length()
              << " ,rows: " << selected.frame.get_rows() << '\n';
    exit(1);
  }

  selected.frame.setup(selected.length, selected.rows, selected.interval);

  for (;;)
  {
    selected.frame.spin(&light);
    std::this_thread::sleep_for(std::chrono::milliseconds(selected.frame.get_interval()));
  }
}
