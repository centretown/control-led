#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Filer.h"
#include "../src/build_catalog.h"

using namespace glow;

TEST_CASE("Library Code", "[catalog_make_code]")
{
  REQUIRE(Chroma::load_palette(palette_file()));

  std::string frame_name = "frame";
  Frame frame;
  REQUIRE(load_yaml(custom_frame(frame_name), frame));

  std::string salmon_name = "salmon-strawberry";
  Frame salmon;
  REQUIRE(load_yaml(custom_frame(salmon_name), salmon));

  add_frame_to_catalog(frame_name, frame);
  add_frame_to_catalog(salmon_name, salmon);

  std::cout << make_code_from_catalog("catalog");
  REQUIRE(make_files_from_catalog("catalog"));
}