#pragma once
#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>

template <typename GLOW_STRUCT>
bool load_yaml(const std::string file_name, GLOW_STRUCT &glow_struct)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_name);
  }
  catch (...)
  {
    return false;
  }

  YAML::convert<GLOW_STRUCT>::decode(node, glow_struct);
  return true;
}

template <typename GLOW_STRUCT>
bool save_yaml(const std::string file_name, const GLOW_STRUCT &glow_struct)
{
  std::fstream fs;
  fs.open(file_name, std::ios_base::out);
  if (fs.bad())
  {
    return false;
  }

  YAML::Node node = YAML::convert<GLOW_STRUCT>::encode(glow_struct);
  YAML::Emitter out;
  out << node;
  fs << out.c_str();
  fs.close();
  return true;
}
