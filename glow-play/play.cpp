#include <signal.h>
#include <thread>

#include <cxxopts.hpp>

#include "ansi_stream.h"
#include "HostLight.h"

#include "catalog.h"

using namespace glow;

void show_lights();
void sigintHandler(int sig_num);
void process_args(int argc, char **argv);
void print_catalog();

uint16_t selected_item = 0;
uint16_t selected_length = 36;
uint16_t selected_rows = 4;
uint32_t selected_interval = 48;
bool selected_catalog = false;

int main(int argc, char **argv)
{
  process_args(argc, argv);
  signal(SIGINT, sigintHandler);
  show_lights();
  exit(0);
}

void process_args(int argc, char **argv)
{
  cxxopts::Options options("glow-play", "Glow Player: led pattern player");

  options.add_options()                                 //
      ("f,frame", "Frame id to play",                   //
       cxxopts::value<uint16_t>()->default_value("0"))  //
      ("l,length", "Length of led strip",               //
       cxxopts::value<uint16_t>()->default_value("36")) //
      ("r,rows", "Rows in light strip",                 //
       cxxopts::value<uint16_t>()->default_value("4"))  //
      ("i,interval", "Interval in ms",                  //
       cxxopts::value<uint32_t>()->default_value("48")) //
      ("c,catalog", "Print catalog")                    //
      ("h,help", "Print usage");                        //

  auto selected = options.parse(argc, argv);

  selected_catalog = selected.count("catalog");

  if (selected.count("help"))
  {
    std::cout << options.help() << std::endl;
    print_catalog();
    exit(0);
  }

  selected_item = selected["frame"].as<uint16_t>();
  selected_length = selected["length"].as<uint16_t>();
  selected_rows = selected["rows"].as<uint16_t>();
  selected_interval = selected["interval"].as<uint32_t>();
}

void sigintHandler(int sig_num)
{
  ansi_at(selected_rows + 1, 0, std::cout);
  ansi_show_cursor(std::cout);
  if (selected_catalog)
  {
    print_catalog();
  }
  exit(0);
};

void show_lights()
{
  ansi_at(0, 0, std::cout);
  ansi_clear_from_cursor(std::cout);
  ansi_hide_cursor(std::cout);

  HostLight light;
  Frame frame = from_catalog((LIBRARY_INDEX)selected_item);
  frame.setup(selected_length, selected_rows, selected_interval);

  light.setup(selected_length, selected_rows);

  for (;;)
  {
    frame.spin(&light);
    std::this_thread::sleep_for(std::chrono::milliseconds(frame.get_interval()));
  }
}

void print_catalog()
{
  std::cout << "\nFrame Catalog:\n";
  for (auto i = 0; i < FRAME_COUNT; i++)
  {
    std::cout << "  id: (" << i << ")  name: " << catalog_name((LIBRARY_INDEX)i) << "\n";
  }
  std::cout << "\n\n";
}