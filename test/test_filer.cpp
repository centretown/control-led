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
  REQUIRE("/home/dave/src/glow/data/frames/frame.yaml" == frame_file());
  REQUIRE("/home/dave/src/glow/data/frames/frame_symbolic.yaml" == frame_symbolic_file());
  REQUIRE("/home/dave/src/glow/data/layers/layer.yaml" == layer_file());
  REQUIRE("/home/dave/src/glow/data/layers/layer_symbolic.yaml" == layer_symbolic_file());
  REQUIRE("/home/dave/src/glow/data/chromas/chroma.yaml" == chroma_file());
  REQUIRE("/home/dave/src/glow/data/chromas/chroma_symbolic.yaml" == chroma_symbolic_file());
  REQUIRE("/home/dave/src/glow/data/grids/grid.yaml" == grid_file());
  REQUIRE("/home/dave/src/glow/data/grids/grid_symbolic.yaml" == grid_symbolic_file());

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
  REQUIRE("data/frames/frame.yaml" == frame_file());
  REQUIRE("data/frames/frame_symbolic.yaml" == frame_symbolic_file());
  REQUIRE("data/layers/layer.yaml" == layer_file());
  REQUIRE("data/layers/layer_symbolic.yaml" == layer_symbolic_file());
  REQUIRE("data/chromas/chroma.yaml" == chroma_file());
  REQUIRE("data/chromas/chroma_symbolic.yaml" == chroma_symbolic_file());
  REQUIRE("data/grids/grid.yaml" == grid_file());
  REQUIRE("data/grids/grid_symbolic.yaml" == grid_symbolic_file());

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
  REQUIRE("data/frames/frame.yaml" == frame_file());
  REQUIRE("data/frames/frame_symbolic.yaml" == frame_symbolic_file());
  REQUIRE("data/layers/layer.yaml" == layer_file());
  REQUIRE("data/layers/layer_symbolic.yaml" == layer_symbolic_file());
  REQUIRE("data/chromas/chroma.yaml" == chroma_file());
  REQUIRE("data/chromas/chroma_symbolic.yaml" == chroma_symbolic_file());
  REQUIRE("data/grids/grid.yaml" == grid_file());
  REQUIRE("data/grids/grid_symbolic.yaml" == grid_symbolic_file());
}