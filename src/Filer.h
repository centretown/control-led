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
  std::fstream yaml_stream;
  yaml_stream.open(file_name, std::ios_base::out);
  if (yaml_stream.bad())
  {
    return false;
  }

  YAML::Emitter out;
  YAML::Node node = YAML::convert<GLOW_STRUCT>::encode(glow_struct);
  out << node;
  yaml_stream << out.c_str();
  yaml_stream.close();
  return true;
}
