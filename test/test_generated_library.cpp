#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "DisplayANSI.h"
#include "HostLight.h"

#include "library.h"

using namespace glow;

TEST_CASE("Library Spin Code", "[library_spin_code]")
{
  HostLight light;
  Frame frame = from_library(SALMON_STRAWBERRY);
  light.setup(frame.get_length(), frame.get_rows());
  frame.spin(&light);
}
