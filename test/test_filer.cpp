#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>

#include "../src/Filer.h"

using namespace glow;

TEST_CASE("Filer Basic", "filer_basic")
{
  set_data_path("/home/dave/src/glow/data");
  REQUIRE("/home/dave/src/glow/data/" == data_path());

  std::cout << palette_file() << '\n';
  std::cout << frame_file() << '\n';
  std::cout << frame_symbolic_file() << '\n';
  std::cout << layer_file() << '\n';
  std::cout << layer_symbolic_file() << '\n';
  std::cout << chroma_file() << '\n';
  std::cout << chroma_symbolic_file() << '\n';
  std::cout << grid_file() << '\n';
  std::cout << grid_symbolic_file() << '\n';

  REQUIRE("/home/dave/src/glow/data/palettes/palette.yaml" == palette_file());
  REQUIRE("/home/dave/src/glow/data/frames/derived/frame.yaml" == frame_file());
  REQUIRE("/home/dave/src/glow/data/frames/symbols/frame_symbolic.yaml" == frame_symbolic_file());
  REQUIRE("/home/dave/src/glow/data/layers/derived/layer.yaml" == layer_file());
  REQUIRE("/home/dave/src/glow/data/layers/symbols/layer_symbolic.yaml" == layer_symbolic_file());
  REQUIRE("/home/dave/src/glow/data/chromas/derived/chroma.yaml" == chroma_file());
  REQUIRE("/home/dave/src/glow/data/chromas/symbols/chroma_symbolic.yaml" == chroma_symbolic_file());
  REQUIRE("/home/dave/src/glow/data/grids/derived/grid.yaml" == grid_file());
  REQUIRE("/home/dave/src/glow/data/grids/symbols/grid_symbolic.yaml" == grid_symbolic_file());

  set_data_path("data");

  std::cout << palette_file() << '\n';
  std::cout << frame_file() << '\n';
  std::cout << frame_symbolic_file() << '\n';
  std::cout << layer_file() << '\n';
  std::cout << layer_symbolic_file() << '\n';
  std::cout << chroma_file() << '\n';
  std::cout << chroma_symbolic_file() << '\n';
  std::cout << grid_file() << '\n';
  std::cout << grid_symbolic_file() << '\n';

  REQUIRE("data/palettes/palette.yaml" == palette_file());
  REQUIRE("data/frames/derived/frame.yaml" == frame_file());
  REQUIRE("data/frames/symbols/frame_symbolic.yaml" == frame_symbolic_file());
  REQUIRE("data/layers/derived/layer.yaml" == layer_file());
  REQUIRE("data/layers/symbols/layer_symbolic.yaml" == layer_symbolic_file());
  REQUIRE("data/chromas/derived/chroma.yaml" == chroma_file());
  REQUIRE("data/chromas/symbols/chroma_symbolic.yaml" == chroma_symbolic_file());
  REQUIRE("data/grids/derived/grid.yaml" == grid_file());
  REQUIRE("data/grids/symbols/grid_symbolic.yaml" == grid_symbolic_file());

  set_data_path("data/");

  std::cout << palette_file() << '\n';
  std::cout << frame_file() << '\n';
  std::cout << frame_symbolic_file() << '\n';
  std::cout << layer_file() << '\n';
  std::cout << layer_symbolic_file() << '\n';
  std::cout << chroma_file() << '\n';
  std::cout << chroma_symbolic_file() << '\n';
  std::cout << grid_file() << '\n';
  std::cout << grid_symbolic_file() << '\n';

  REQUIRE("data/palettes/palette.yaml" == palette_file());
  REQUIRE("data/frames/derived/frame.yaml" == frame_file());
  REQUIRE("data/frames/symbols/frame_symbolic.yaml" == frame_symbolic_file());
  REQUIRE("data/layers/derived/layer.yaml" == layer_file());
  REQUIRE("data/layers/symbols/layer_symbolic.yaml" == layer_symbolic_file());
  REQUIRE("data/chromas/derived/chroma.yaml" == chroma_file());
  REQUIRE("data/chromas/symbols/chroma_symbolic.yaml" == chroma_symbolic_file());
  REQUIRE("data/grids/derived/grid.yaml" == grid_file());
  REQUIRE("data/grids/symbols/grid_symbolic.yaml" == grid_symbolic_file());

}