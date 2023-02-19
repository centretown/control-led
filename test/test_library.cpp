#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Filer.h"
#include "../src/Library.h"
using namespace glow;

TEST_CASE("Library Code", "[library_make_code]")
{
  REQUIRE(Chroma::load_palette(palette_file()));

  std::string frame_name = "frame";
  Frame frame;
  REQUIRE(load_yaml(custom_frame(frame_name), frame));

  std::string salmon_name = "salmon-strawberry";
  Frame salmon;
  REQUIRE(load_yaml(custom_frame(salmon_name), salmon));

  add_frame_to_library(frame_name, frame);
  add_frame_to_library(salmon_name, salmon);

  std::cout << make_code_from_library("library");
  REQUIRE(make_files_from_library("library"));
}