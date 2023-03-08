#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <catch2/catch_all.hpp>

#include "test_yaml.h"
#include "Grid.h"
#include "check_grid_detail.h"

using namespace glow;

void check_detail(const Grid &original, const Grid &derived)
{
  check_grid_detail(original, derived);
}

TEST_CASE("Grid 2x2 TopLeft Diagonal", "[grid_2x2_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(4, 2, TopLeft, Diagonal));
  REQUIRE(4 == grid.get_length());
  REQUIRE(2 == grid.get_rows());
  REQUIRE(TopLeft == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());
  REQUIRE(1 == grid.get_first());
  REQUIRE(1 == grid.get_offset());

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(2 == grid.map(2));
  REQUIRE(3 == grid.map(3));

  std::string input =
      "length: 4\n"
      "rows: 2\n"
      "origin: 0\n"
      "orientation: diagonal\n";
  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid 2x3 TopLeft Diagonal", "[grid_2x3_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(6, 2, TopLeft, Diagonal));
  REQUIRE(6 == grid.get_length());
  REQUIRE(2 == grid.get_rows());
  REQUIRE(TopLeft == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());
  REQUIRE(1 == grid.get_first());
  REQUIRE(1 == grid.get_offset());
  REQUIRE(4 == grid.get_last());

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
      "orientation: diagonal\n";

  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid 3x4 TopLeft Diagonal", "[grid_3x4_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(12, 3, TopLeft, Diagonal));
  REQUIRE(12 == grid.get_length());
  REQUIRE(3 == grid.get_rows());
  REQUIRE(TopLeft == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());

  REQUIRE(3 == grid.get_first());
  REQUIRE(2 == grid.get_offset());
  REQUIRE(8 == grid.get_last());

  REQUIRE(0 == grid.map(0));
  REQUIRE(1 == grid.map(1));
  REQUIRE(4 == grid.map(2));
  REQUIRE(2 == grid.map(3));
  REQUIRE(5 == grid.map(4));
  REQUIRE(8 == grid.map(5));
  bool setup();
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
      "orientation: diagonal\n";

  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid 4x5 TopLeft Diagonal", "[grid_4x5_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(20, 4, TopLeft, Diagonal));
  REQUIRE(20 == grid.get_length());
  REQUIRE(4 == grid.get_rows());
  REQUIRE(TopLeft == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());

  REQUIRE(5 == grid.get_columns());

  REQUIRE(6 == grid.get_first());
  REQUIRE(3 == grid.get_offset());
  REQUIRE(13 == grid.get_last());

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
      "orientation: diagonal\n";

  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid 4x9 TopLeft Diagonal", "[grid_4x9_topleft_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 4, TopLeft, Diagonal));
  REQUIRE(36 == grid.get_length());
  REQUIRE(4 == grid.get_rows());
  REQUIRE(TopLeft == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());

  REQUIRE(9 == grid.get_columns());

  REQUIRE(6 == grid.get_first());
  REQUIRE(3 == grid.get_offset());
  REQUIRE(29 == grid.get_last());

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
      "orientation: diagonal\n";

  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid 4x9 TopRight Diagonal", "[grid_4x9_topright_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 4, TopRight, Diagonal));
  REQUIRE(36 == grid.get_length());
  REQUIRE(4 == grid.get_rows());
  REQUIRE(TopRight == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());

  REQUIRE(9 == grid.get_columns());

  REQUIRE(6 == grid.get_first());
  REQUIRE(3 == grid.get_offset());
  REQUIRE(29 == grid.get_last());

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
      "origin: top right\n"
      "orientation: diagonal\n";

  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid 4x9 BottomRight Diagonal", "[grid_4x9_bottomright_diagonal]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 4, BottomRight, Diagonal));
  REQUIRE(36 == grid.get_length());
  REQUIRE(4 == grid.get_rows());
  REQUIRE(BottomRight == grid.get_origin());
  REQUIRE(Diagonal == grid.get_orientation());

  REQUIRE(9 == grid.get_columns());

  REQUIRE(6 == grid.get_first());
  REQUIRE(3 == grid.get_offset());
  REQUIRE(29 == grid.get_last());

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
      "origin: bottom right\n"
      "orientation: diagonal\n";

  test_yaml(grid, input, check_detail);
}

TEST_CASE("Grid Symbolic", "[grid_custom]")
{
  Grid grid_default_rows;
  REQUIRE(grid_default_rows.setup(36, 1, BottomRight, Diagonal));
  std::string input_missing_rows =
      "length: 36\n"
      "origin: bottom right\n"
      "orientation: diagonal\n";
  test_yaml_from_input(grid_default_rows,
                       input_missing_rows, check_detail);

  Grid grid_default_origin;
  REQUIRE(grid_default_origin.setup(36, 4, TopLeft, Diagonal));
  std::string input_missing_origin =
      "length: 36\n"
      "rows: 4\n"
      "orientation: diagonal\n";
  test_yaml_from_input(grid_default_origin,
                       input_missing_origin, check_detail);

  Grid grid_default_orientation;
  REQUIRE(grid_default_orientation.setup(36, 4, BottomRight, Horizontal));
  std::string input_missing_orientation =
      "length: 36\n"
      "rows: 4\n"
      "origin: bottom right\n";
  test_yaml_from_input(grid_default_orientation,
                       input_missing_orientation, check_detail);
}

TEST_CASE("Grid Incomplete", "[grid_incomplete]")
{
  Grid grid_default_length;
  REQUIRE(grid_default_length.setup(10, 4));
  std::string input_missing_half =
      "length: 10\n"
      "rows: 4\n";
  // test_yaml_from_input(grid_default_length,
  //                      input_missing_half, check_detail);

  Grid grid_default_rows;
  REQUIRE(grid_default_rows.setup(36, 1, BottomRight, Diagonal));
  std::string input_missing_rows =
      "length: 36\n"
      "origin: bottom right\n"
      "orientation: diagonal\n";
  test_yaml_from_input(grid_default_rows,
                       input_missing_rows, check_detail);

  Grid grid_default_origin;
  REQUIRE(grid_default_origin.setup(36, 4, TopLeft, Diagonal));
  std::string input_missing_origin =
      "length: 36\n"
      "rows: 4\n"
      "orientation: diagonal\n";
  test_yaml_from_input(grid_default_origin,
                       input_missing_origin, check_detail);

  Grid grid_default_orientation;
  REQUIRE(grid_default_orientation.setup(36, 4, BottomRight, Horizontal));
  std::string input_missing_orientation =
      "length: 36\n"
      "rows: 4\n"
      "origin: bottom right\n";
  test_yaml_from_input(grid_default_orientation,
                       input_missing_orientation, check_detail);

  Grid grid_default;
  REQUIRE(grid_default.setup(36));
  std::string input_missing =
      "length: 36\n";
  test_yaml_from_input(grid_default,
                       input_missing, check_detail);
}

TEST_CASE("Grid Code", "[grid_make_code]")
{
  Grid grid;
  REQUIRE(grid.setup(36, 1, BottomRight, Diagonal));
  std::cout << grid.make_code() << '\n';
  REQUIRE(grid.setup(36, 4, TopRight, Horizontal));
  std::cout << grid.make_code() << '\n';
  REQUIRE(grid.setup(33, 1, BottomLeft, Vertical));
  std::cout << grid.make_code() << '\n';
  REQUIRE(grid.setup(44, 3, TopLeft, Diagonal));
  std::cout << grid.make_code() << '\n';
  REQUIRE(grid.setup(66, 1, BottomRight, Diagonal));
  std::cout << grid.make_code() << '\n';
}
