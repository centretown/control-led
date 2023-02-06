#pragma once
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../src/Frame.h"
using namespace glow;

#include "check_chroma_detail.h"
#include "check_grid_detail.h"
#include "check_layer_detail.h"

void check_frame_detail(const Frame &original, const Frame &derived)
{
  REQUIRE(original.get_length() == derived.get_length());
  REQUIRE(original.get_interval() == derived.get_interval());
  REQUIRE(original.get_size() == derived.get_size());

  auto iter_original = original.begin();
  auto iter_derived = derived.begin();
  while (iter_original != original.end())
  {
    check_layer_detail(*iter_original, *iter_derived);

    ++iter_original;
    ++iter_derived;
  }
}
