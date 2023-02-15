#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>

#include "../src/Filer.h"

using namespace glow;

const std::string frame_name = "frame";
const std::string layer_name = "layer";
const std::string chroma_name = "chroma";
const std::string grid_name = "grid";

TEST_CASE("Filer Basic", "filer_basic")
{
  set_data_path("/home/dave/src/glow/data");
  REQUIRE("/home/dave/src/glow/data/" == data_path());

  std::cout << palette_file() << '\n';
  std::cout << derived_frame(frame_name) << '\n';
  std::cout << custom_frame(frame_name) << '\n';
  std::cout << derived_layer(layer_name) << '\n';
  std::cout << custom_layer(layer_name) << '\n';
  std::cout << derived_chroma(chroma_name) << '\n';
  std::cout << custom_chroma(chroma_name) << '\n';
  std::cout << derived_grid(grid_name) << '\n';
  std::cout << custom_grid(grid_name) << '\n';

  REQUIRE("/home/dave/src/glow/data/palettes/palette.yaml" == palette_file());
  REQUIRE("/home/dave/src/glow/data/frames/derived/frame.yaml" == derived_frame(frame_name));
  REQUIRE("/home/dave/src/glow/data/frames/custom/frame.yaml" == custom_frame(frame_name));
  REQUIRE("/home/dave/src/glow/data/layers/derived/layer.yaml" == derived_layer(layer_name));
  REQUIRE("/home/dave/src/glow/data/layers/custom/layer.yaml" == custom_layer(layer_name));
  REQUIRE("/home/dave/src/glow/data/chromas/derived/chroma.yaml" == derived_chroma(chroma_name));
  REQUIRE("/home/dave/src/glow/data/chromas/custom/chroma.yaml" == custom_chroma(chroma_name));
  REQUIRE("/home/dave/src/glow/data/grids/derived/grid.yaml" == derived_grid(grid_name));
  REQUIRE("/home/dave/src/glow/data/grids/custom/grid.yaml" == custom_grid(grid_name));

  set_data_path("data");

  std::cout << palette_file() << '\n';
  std::cout << derived_frame(frame_name) << '\n';
  std::cout << custom_frame(frame_name) << '\n';
  std::cout << derived_layer(layer_name) << '\n';
  std::cout << custom_layer(layer_name) << '\n';
  std::cout << derived_chroma(chroma_name) << '\n';
  std::cout << custom_chroma(chroma_name) << '\n';
  std::cout << derived_grid(grid_name) << '\n';
  std::cout << custom_grid(grid_name) << '\n';

  REQUIRE("data/palettes/palette.yaml" == palette_file());
  REQUIRE("data/frames/derived/frame.yaml" == derived_frame(frame_name));
  REQUIRE("data/frames/custom/frame.yaml" == custom_frame(frame_name));
  REQUIRE("data/layers/derived/layer.yaml" == derived_layer(layer_name));
  REQUIRE("data/layers/custom/layer.yaml" == custom_layer(layer_name));
  REQUIRE("data/chromas/derived/chroma.yaml" == derived_chroma(chroma_name));
  REQUIRE("data/chromas/custom/chroma.yaml" == custom_chroma(chroma_name));
  REQUIRE("data/grids/derived/grid.yaml" == derived_grid(grid_name));
  REQUIRE("data/grids/custom/grid.yaml" == custom_grid(grid_name));

  set_data_path("data/");

  std::cout << palette_file() << '\n';
  std::cout << derived_frame(frame_name) << '\n';
  std::cout << custom_frame(frame_name) << '\n';
  std::cout << derived_layer(layer_name) << '\n';
  std::cout << custom_layer(layer_name) << '\n';
  std::cout << derived_chroma(chroma_name) << '\n';
  std::cout << custom_chroma(chroma_name) << '\n';
  std::cout << derived_grid(grid_name) << '\n';
  std::cout << custom_grid(grid_name) << '\n';

  REQUIRE("data/palettes/palette.yaml" == palette_file());
  REQUIRE("data/frames/derived/frame.yaml" == derived_frame(frame_name));
  REQUIRE("data/frames/custom/frame.yaml" == custom_frame(frame_name));
  REQUIRE("data/layers/derived/layer.yaml" == derived_layer(layer_name));
  REQUIRE("data/layers/custom/layer.yaml" == custom_layer(layer_name));
  REQUIRE("data/chromas/derived/chroma.yaml" == derived_chroma(chroma_name));
  REQUIRE("data/chromas/custom/chroma.yaml" == custom_chroma(chroma_name));
  REQUIRE("data/grids/derived/grid.yaml" == derived_grid(grid_name));
  REQUIRE("data/grids/custom/grid.yaml" == custom_grid(grid_name));
}