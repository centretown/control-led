#include "DisplayANSI.h"
#include "HostLight.h"

#include "library.h"

using namespace glow;

int main()
{
  HostLight light;
  Frame frame(from_library(SALMON_STRAWBERRY));
  light.setup(frame.get_length(), frame.get_rows());
  frame.spin(&light);
}