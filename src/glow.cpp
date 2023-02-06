#include <iostream>

#include <yaml-cpp/yaml.h>
#include "Grid.h"
using namespace glow;
// using namespace YAML;

int main(int argc, char **argv)
{
  Grid grid;
  grid.setup(20, 4, BottomLeft, Diagonal);
  std::cout << "length:" << grid.get_length() << std::endl;
  std::cout << "rows:" << grid.get_rows() << std::endl;
  std::cout << "origin:" << grid.get_origin() << std::endl;
  std::cout << "orientation:" << grid.get_orientation() << std::endl;
  std::cout << "columns:" << grid.get_columns() << std::endl;
  std::cout << "pivot.first:" << grid.get_first() << std::endl;
  std::cout << "pivot.last:" << grid.get_last() << std::endl;
  std::cout << "pivot.offset:" << grid.get_offset() << std::endl
            << std::endl;

  YAML::Node node = YAML::convert<Grid>::encode(grid);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << std::endl;

  return 0;
}