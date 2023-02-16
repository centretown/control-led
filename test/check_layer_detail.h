#pragma once
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>
#include <string>

#include "../src/Layer.h"

#include "check_chroma_detail.h"
#include "check_grid_detail.h"

using namespace glow;

void check_layer_detail(const Layer &original, const Layer &derived)
{

  REQUIRE(original.get_length() == derived.get_length());
  REQUIRE(original.get_rows() == derived.get_rows());
  REQUIRE(original.get_begin() == derived.get_begin());
  REQUIRE(original.get_end() == derived.get_end());

  check_grid_detail(original.get_grid(), derived.get_grid());
  check_chroma_detail(original.get_chroma(), derived.get_chroma());
}
