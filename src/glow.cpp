#include <iostream>
#include <string>
#include <signal.h>
#include <cxxopts.hpp>

#include "GlowConfig.h"

#include "glow_file.h"
#include "glow_show.h"

struct Selections
{
  std::string data_path;
  std::string show_frame;
  std::vector<std::string> frames_to_add;

  uint16_t length = 36;
  uint16_t rows = 4;
  uint32_t interval = 48;

  bool show_palette = false;
  uint16_t show_columns = 5;
  uint16_t show_column_width = 26;

  bool show_catalog = false;
  bool build_catalog = false;
  bool help = false;
};

void process_command_line(int argc, char **argv, Selections &selections);
int process_selections(Selections &selections);

int main(int argc, char **argv)
{
  Selections selections;

  process_command_line(argc, argv, selections);

  auto status = process_selections(selections);

  return status;
}

void process_command_line(int argc, char **argv, Selections &selections)
{
  cxxopts::Options options("glow", "colorize and animate addressable LED's");

  options.add_options()                                                  //
      ("d,data", "Set pcpath to data",                                   //
       cxxopts::value<std::string>()->default_value(file_system_path())) //
      ("s,show", "Show frame by name (Ctrl-c to exit)",                  //
       cxxopts::value<std::string>()->default_value("glow"))             //
      ("l,length", "Length of led strip",                                //
       cxxopts::value<uint16_t>()->default_value("36"))                  //
      ("r,rows", "Rows in led strip",                                    //
       cxxopts::value<uint16_t>()->default_value("4"))                   //
      ("i,interval", "Interval in ms",                                   //
       cxxopts::value<uint32_t>()->default_value("48"))                  //

      ("p,palette", "Print current palette")            //
      ("n,columns", "Columns to print",                 //
       cxxopts::value<uint16_t>()->default_value("5"))  //
      ("w,column-width", "Column Width to print",       //
       cxxopts::value<uint16_t>()->default_value("26")) //

      ("c,catalog", "Print catalog")                                  //
      ("a,add", "Add to catalog",                                     //
       cxxopts::value<std::vector<std::string>>()->default_value("")) //
      ("b,build_catalog", "Build catalog")                            //
      ("h,help", "Print usage");                                      //

  options.allow_unrecognised_options();
  cxxopts::ParseResult parsed = options.parse(argc, argv);

  selections.data_path = parsed["data"].as<std::string>();
  selections.show_frame = parsed["show"].as<std::string>();
  selections.length = parsed["length"].as<uint16_t>();
  selections.rows = parsed["rows"].as<uint16_t>();
  selections.interval = parsed["interval"].as<uint32_t>();
  selections.show_columns = parsed["columns"].as<uint16_t>();
  selections.show_column_width = parsed["column-width"].as<uint16_t>();
  selections.show_catalog = parsed.count("catalog");
  selections.show_palette = parsed.count("palette");
  selections.build_catalog = parsed.count("build_catalog");
  selections.frames_to_add = parsed["add"].as<std::vector<std::string>>();
  selections.help = parsed.count("help");

  cxxopts::PositionalList unmatched = parsed.unmatched();
  if (unmatched.size() > 0)
  {
    for (auto &x : unmatched)
    {
      std::cout << "Unrecogized option: " << x.c_str() << '\n';
    }
    selections.help = true;
  }

  if (selections.help)
  {
    std::cout << "Glow Version: " << Glow_VERSION_MAJOR << '.' << Glow_VERSION_MINOR << '\n';
    std::cout << options.help() << '\n';
  }
}

int create_file_system(std::string data_path)
{
  std::string message;
  if (file_system_create(data_path, message) ==
      false)
  {
    std::cout << message << '\n';
    return EXIT_FAILURE;
  }
  std::cout << message << '\n';
  return EXIT_SUCCESS;
}

int add_frames_to_catalog(std::vector<std::string> frames_to_add)
{
  std::string message;

  if (file_catalog_copy(frames_to_add, message) ==
      false)
  {
    std::cout << message << '\n';
    return EXIT_FAILURE;
  }

  std::cout << message << '\n';
  return EXIT_SUCCESS;
}

int display_catalog()
{
  std::vector<std::string> frame_names;
  file_catalog_list(frame_names);
  for (auto &name : frame_names)
  {
    std::cout << name << '\n';
  }
  return EXIT_SUCCESS;
}

int build_catalog()
{
  std::string message;
  file_catalog_build(message);
  std::cout << message << '\n';
  return EXIT_SUCCESS;
}

int process_selections(Selections &selections)
{
  if (selections.help)
  {
    return EXIT_SUCCESS;
  }

  if (file_system_exists(selections.data_path) ==
      false)
  {
    return create_file_system(selections.data_path);
  }

  if (selections.frames_to_add.size() > 0 &&
      selections.frames_to_add[0].size() > 0)
  {
    return add_frames_to_catalog(selections.frames_to_add);
  }

  if (selections.show_catalog)
  {
    return display_catalog();
  }

  std::string message;
  if (file_load_palette(message) ==
      false)
  {
    std::cout << message << '\n';
    return EXIT_FAILURE;
  }

  if (selections.build_catalog)
  {
    return build_catalog();
  }

  if (selections.show_palette ==
      true)
  {
    show_palette(selections.show_columns, selections.show_column_width);
    return EXIT_SUCCESS;
  }

  signal(SIGINT, [](int)
         {show_normal();exit(EXIT_SUCCESS); });

  if (show_lights(selections.length, selections.rows, selections.interval,
                  selections.show_frame, message) ==
      false)
  {
    std::cout << message << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}