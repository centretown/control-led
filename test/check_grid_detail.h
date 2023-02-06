#pragma once

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <catch2/catch_all.hpp>

#include "../src/Grid.h"
using namespace glow;

void check_grid_detail(const Grid &original, const Grid &derived)
{
  REQUIRE(original.get_length() == derived.get_length());
  REQUIRE(original.get_rows() == derived.get_rows());
  REQUIRE(original.get_origin() == derived.get_origin());
  REQUIRE(original.get_orientation() == derived.get_orientation());
  REQUIRE(original.get_first() == derived.get_first());
  REQUIRE(original.get_offset() == derived.get_offset());
  REQUIRE(original.get_last() == derived.get_last());
}
