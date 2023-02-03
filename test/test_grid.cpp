#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <catch2/catch_all.hpp>
#include <yaml-cpp/yaml.h>

#include "../src/Grid.h"

using namespace glow;

void test_yaml(Grid &grid, std::string input)
{
  YAML::Node node = YAML::convert<Grid>::encode(grid);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl;
  Grid grid_from_node;
  YAML::convert<Grid>::decode(node, grid_from_node);
  REQUIRE(grid == grid_from_node);

  YAML::Node input_node = YAML::Load(input);
  Grid grid_from_input;
  YAML::convert<Grid>::decode(input_node, grid_from_input);
  REQUIRE(grid == grid_from_input);
}

TEST_CASE("Grid 2x2 TopLeft Diagonal", "[grid_2x2_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(4, 2, TopLeft, Diagonal));
  REQUIRE(4 == grid.length);
  REQUIRE(2 == grid.rows);
  REQUIRE(TopLeft == grid.origin);
  REQUIRE(Diagonal == grid.orientation);
  REQUIRE(1 == grid.pivot.first);
  REQUIRE(1 == grid.pivot.offset);

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(2 == grid.map(2));
  REQUIRE(3 == grid.map(3));

  std::string input =
      "length: 4\n"
      "rows: 2\n"
      "origin: 0\n"
      "orientation: 2\n";
  test_yaml(grid, input);
}

TEST_CASE("Grid 2x3 TopLeft Diagonal", "[grid_2x3_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(6, 2, TopLeft, Diagonal));
  REQUIRE(6 == grid.length);
  REQUIRE(2 == grid.rows);
  REQUIRE(TopLeft == grid.origin);
  REQUIRE(Diagonal == grid.orientation);
  REQUIRE(1 == grid.pivot.first);
  REQUIRE(1 == grid.pivot.offset);
  REQUIRE(4 == grid.pivot.last);

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(3 == grid.map(2));
  REQUIRE(2 == grid.map(3));
  REQUIRE(4 == grid.map(4));
  REQUIRE(5 == grid.map(5));

  std::string input =
      "length: 6\n"
      "rows: 2\n"
      "origin: 0\n"
      "orientation: 2\n";

  test_yaml(grid, input);
}

TEST_CASE("Grid 3x4 TopLeft Diagonal", "[grid_3x4_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(12, 3, TopLeft, Diagonal));
  REQUIRE(12 == grid.length);
  REQUIRE(3 == grid.rows);
  REQUIRE(TopLeft == grid.origin);
  REQUIRE(Diagonal == grid.orientation);

  REQUIRE(3 == grid.pivot.first);
  REQUIRE(2 == grid.pivot.offset);
  REQUIRE(8 == grid.pivot.last);

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(4 == grid.map(2));
  REQUIRE(2 == grid.map(3));
  REQUIRE(5 == grid.map(4));
  REQUIRE(8 == grid.map(5));
  REQUIRE(3 == grid.map(6));
  REQUIRE(6 == grid.map(7));
  REQUIRE(9 == grid.map(8));
  REQUIRE(7 == grid.map(9));
  REQUIRE(10 == grid.map(10));
  REQUIRE(11 == grid.map(11));

  std::string input =
      "length: 12\n"
      "rows: 3\n"
      "origin: 0\n"
      "orientation: 2\n";

  test_yaml(grid, input);
}

TEST_CASE("Grid 4x5 TopLeft Diagonal", "[grid_4x5_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));
  REQUIRE(20 == grid.length);
  REQUIRE(4 == grid.rows);
  REQUIRE(TopLeft == grid.origin);
  REQUIRE(Diagonal == grid.orientation);

  REQUIRE(5 == grid.columns);

  REQUIRE(6 == grid.pivot.first);
  REQUIRE(3 == grid.pivot.offset);
  REQUIRE(13 == grid.pivot.last);

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(5 == grid.map(2));
  REQUIRE(2 == grid.map(3));
  REQUIRE(6 == grid.map(4));
  REQUIRE(10 == grid.map(5));
  REQUIRE(3 == grid.map(6));
  REQUIRE(7 == grid.map(7));
  REQUIRE(11 == grid.map(8));
  REQUIRE(15 == grid.map(9));
  REQUIRE(4 == grid.map(10));
  REQUIRE(8 == grid.map(11));
  REQUIRE(12 == grid.map(12));
  REQUIRE(16 == grid.map(13));
  REQUIRE(9 == grid.map(14));
  REQUIRE(13 == grid.map(15));
  REQUIRE(17 == grid.map(16));
  REQUIRE(14 == grid.map(17));
  REQUIRE(18 == grid.map(18));
  REQUIRE(19 == grid.map(19));

  std::string input =
      "length: 20\n"
      "rows: 4\n"
      "origin: 0\n"
      "orientation: 2\n";

  test_yaml(grid, input);
}

TEST_CASE("Grid 4x9 TopLeft Diagonal", "[grid_4x9_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 4, TopLeft, Diagonal));
  REQUIRE(36 == grid.length);
  REQUIRE(4 == grid.rows);
  REQUIRE(TopLeft == grid.origin);
  REQUIRE(Diagonal == grid.orientation);

  REQUIRE(9 == grid.columns);

  REQUIRE(6 == grid.pivot.first);
  REQUIRE(3 == grid.pivot.offset);
  REQUIRE(29 == grid.pivot.last);

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(9 == grid.map(2));
  REQUIRE(2 == grid.map(3));
  REQUIRE(10 == grid.map(4));
  REQUIRE(18 == grid.map(5));
  REQUIRE(3 == grid.map(6));
  REQUIRE(11 == grid.map(7));
  REQUIRE(19 == grid.map(8));
  REQUIRE(27 == grid.map(9));
  REQUIRE(4 == grid.map(10));
  REQUIRE(12 == grid.map(11));
  REQUIRE(20 == grid.map(12));
  REQUIRE(28 == grid.map(13));
  REQUIRE(5 == grid.map(14));
  REQUIRE(13 == grid.map(15));
  REQUIRE(21 == grid.map(16));
  REQUIRE(29 == grid.map(17));
  REQUIRE(6 == grid.map(18));
  REQUIRE(14 == grid.map(19));
  REQUIRE(22 == grid.map(20));
  REQUIRE(30 == grid.map(21));
  REQUIRE(7 == grid.map(22));
  REQUIRE(15 == grid.map(23));
  REQUIRE(23 == grid.map(24));
  REQUIRE(31 == grid.map(25));
  REQUIRE(8 == grid.map(26));
  REQUIRE(16 == grid.map(27));
  REQUIRE(24 == grid.map(28));
  REQUIRE(32 == grid.map(29));
  REQUIRE(17 == grid.map(30));
  REQUIRE(25 == grid.map(31));
  REQUIRE(33 == grid.map(32));
  REQUIRE(26 == grid.map(33));
  REQUIRE(34 == grid.map(34));
  REQUIRE(35 == grid.map(35));

  std::string input =
      "length: 36\n"
      "rows: 4\n"
      "origin: 0\n"
      "orientation: 2\n";

  test_yaml(grid, input);
}

TEST_CASE("Grid 4x9 TopRight Diagonal", "[grid_4x9_topright_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 4, TopRight, Diagonal));
  REQUIRE(36 == grid.length);
  REQUIRE(4 == grid.rows);
  REQUIRE(TopRight == grid.origin);
  REQUIRE(Diagonal == grid.orientation);

  REQUIRE(9 == grid.columns);

  REQUIRE(6 == grid.pivot.first);
  REQUIRE(3 == grid.pivot.offset);
  REQUIRE(29 == grid.pivot.last);

  REQUIRE(8 == grid.map(0));
  REQUIRE(7 == grid.map(1));
  REQUIRE(17 == grid.map(2));
  REQUIRE(6 == grid.map(3));
  REQUIRE(16 == grid.map(4));

  REQUIRE(26 == grid.map(5));
  REQUIRE(5 == grid.map(6));
  REQUIRE(15 == grid.map(7));
  REQUIRE(25 == grid.map(8));
  REQUIRE(35 == grid.map(9));

  REQUIRE(4 == grid.map(10));
  REQUIRE(14 == grid.map(11));
  REQUIRE(24 == grid.map(12));
  REQUIRE(34 == grid.map(13));
  REQUIRE(18 == grid.map(33));
  REQUIRE(28 == grid.map(34));
  REQUIRE(27 == grid.map(35));

  std::string input =
      "length: 36\n"
      "rows: 4\n"
      "origin: 1\n"
      "orientation: 2\n";

  test_yaml(grid, input);
}

TEST_CASE("Grid 4x9 BottomRight Diagonal", "[grid_4x9_bottomright_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 4, BottomRight, Diagonal));
  REQUIRE(36 == grid.length);
  REQUIRE(4 == grid.rows);
  REQUIRE(BottomRight == grid.origin);
  REQUIRE(Diagonal == grid.orientation);

  REQUIRE(9 == grid.columns);

  REQUIRE(6 == grid.pivot.first);
  REQUIRE(3 == grid.pivot.offset);
  REQUIRE(29 == grid.pivot.last);

  REQUIRE(35 == grid.map(0));
  REQUIRE(34 == grid.map(1));
  REQUIRE(26 == grid.map(2));
  REQUIRE(33 == grid.map(3));
  REQUIRE(25 == grid.map(4));
  REQUIRE(17 == grid.map(5));
  REQUIRE(32 == grid.map(6));
  REQUIRE(24 == grid.map(7));
  REQUIRE(16 == grid.map(8));
  REQUIRE(8 == grid.map(9));
  REQUIRE(31 == grid.map(10));
  REQUIRE(23 == grid.map(11));
  REQUIRE(15 == grid.map(12));
  REQUIRE(7 == grid.map(13));
  REQUIRE(30 == grid.map(14));
  REQUIRE(22 == grid.map(15));
  REQUIRE(14 == grid.map(16));
  REQUIRE(6 == grid.map(17));
  REQUIRE(29 == grid.map(18));
  REQUIRE(21 == grid.map(19));
  REQUIRE(13 == grid.map(20));
  REQUIRE(5 == grid.map(21));
  REQUIRE(28 == grid.map(22));
  REQUIRE(20 == grid.map(23));
  REQUIRE(12 == grid.map(24));
  REQUIRE(4 == grid.map(25));
  REQUIRE(27 == grid.map(26));
  REQUIRE(19 == grid.map(27));
  REQUIRE(11 == grid.map(28));
  REQUIRE(3 == grid.map(29));

  REQUIRE(18 == grid.map(30));
  REQUIRE(10 == grid.map(31));

  REQUIRE(2 == grid.map(32));
  REQUIRE(9 == grid.map(33));
  REQUIRE(1 == grid.map(34));
  REQUIRE(0 == grid.map(35));

  std::string input =
      "length: 36\n"
      "rows: 4\n"
      "origin: 3\n"
      "orientation: 2\n";

  test_yaml(grid, input);
}
