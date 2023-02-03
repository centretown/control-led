#include <iostream>

#include <yaml-cpp/yaml.h>
#include "Grid.h"
using namespace glow;
// using namespace YAML;

int main(int argc, char **argv)
{
  Grid grid;
  grid.setup(20, 4, BottomLeft, Diagonal);
  std::cout << "length:" << grid.length << std::endl;
  std::cout << "rows:" << grid.rows << std::endl;
  std::cout << "origin:" << grid.origin << std::endl;
  std::cout << "orientation:" << grid.orientation << std::endl;
  std::cout << "columns:" << grid.columns << std::endl;
  std::cout << "pivot.first:" << grid.pivot.first << std::endl;
  std::cout << "pivot.last:" << grid.pivot.last << std::endl;
  std::cout << "pivot.offset:" << grid.pivot.offset << std::endl
            << std::endl;

  YAML::Node node = YAML::convert<Grid>::encode(grid);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl;

  return 0;
}