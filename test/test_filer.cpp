#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>

#include "../src/Filer.h"

using namespace glow;

const std::string frame_name = "frame";
const std::string layer_name = "layer";
const std::string chroma_name = "chroma";
const std::string grid_name = "grid";

void show_names()
{
  std::cout << palette_file() << '\n';
  std::cout << derived_frame(frame_name) << '\n';
  std::cout << custom_frame(frame_name) << '\n';
  std::cout << derived_layer(layer_name) << '\n';
  std::cout << custom_layer(layer_name) << '\n';
  std::cout << derived_chroma(chroma_name) << '\n';
  std::cout << custom_chroma(chroma_name) << '\n';
  std::cout << derived_grid(grid_name) << '\n';
  std::cout << custom_grid(grid_name) << '\n';
}

void check_names()
{
  REQUIRE("/home/dave/src/glow/test_data/palettes/palette.yaml" == palette_file());
  REQUIRE("/home/dave/src/glow/test_data/frames/derived/frame.yaml" == derived_frame(frame_name));
  REQUIRE("/home/dave/src/glow/test_data/frames/frame.yaml" == custom_frame(frame_name));
  REQUIRE("/home/dave/src/glow/test_data/layers/derived/layer.yaml" == derived_layer(layer_name));
  REQUIRE("/home/dave/src/glow/test_data/layers/layer.yaml" == custom_layer(layer_name));
  REQUIRE("/home/dave/src/glow/test_data/chromas/derived/chroma.yaml" == derived_chroma(chroma_name));
  REQUIRE("/home/dave/src/glow/test_data/chromas/chroma.yaml" == custom_chroma(chroma_name));
  REQUIRE("/home/dave/src/glow/test_data/grids/derived/grid.yaml" == derived_grid(grid_name));
  REQUIRE("/home/dave/src/glow/test_data/grids/grid.yaml" == custom_grid(grid_name));
}

TEST_CASE("Filer Basic", "filer_basic")
{
#ifdef TEST_DATA_DIR
  glow::set_data_path(TEST_DATA_DIR);
#endif

  std::string path = data_path();
  std::cout << path << '\n';

  show_names();
  check_names();
}