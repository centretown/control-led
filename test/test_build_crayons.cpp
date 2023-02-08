#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <catch2/catch_all.hpp>

#include "../src/Crayons.h"

using namespace glow;

TEST_CASE("Build Crayons", "[build_crayons]")
{
  build_crayons();
  for (auto iter : crayons)
  {
    std::cout << iter.first << std::endl
              << "\tRGB: "
              << (uint16_t)iter.second.rgb.red << ", "
              << (uint16_t)iter.second.rgb.green << ", "
              << (uint16_t)iter.second.rgb.blue << std::endl
              << "\tHSV: " << (uint16_t)iter.second.hsv.hue << ", "
              << (uint16_t)iter.second.hsv.saturation << ", "
              << (uint16_t)iter.second.hsv.value << std::endl;
  }
}
