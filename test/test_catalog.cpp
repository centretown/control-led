#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "Filer.h"
#include "build_catalog.h"

using namespace glow;

TEST_CASE("Catalog Code", "[catalog_make_code]")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  REQUIRE(Chroma::load_palette(palette_file()));

  std::string frame_name = "frame";
  Frame frame;
  REQUIRE(load_yaml(custom_frame(frame_name), frame));

  std::string salmon_name = "salmon-strawberry";
  Frame salmon;
  REQUIRE(load_yaml(custom_frame(salmon_name), salmon));

  add_frame_to_catalog(frame_name, frame);
  add_frame_to_catalog(salmon_name, salmon);

  REQUIRE(make_catalog_code());
}

TEST_CASE("Catalog Effects", "[catalog_make_effects]")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif
  std::string strip_name = "strip.yml";
  std::string grid_name = "grid.yml";
  make_catalog_effects(strip_name, 1, 48);
  make_catalog_effects(grid_name, 4, 48);
}
