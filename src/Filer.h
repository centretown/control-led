#pragma once
#include <string>
#include <fstream>
#include <filesystem>

#include <yaml-cpp/yaml.h>

namespace glow
{
  const std::string data_path();
  const std::string set_data_path(std::string path);
  std::string data_path(std::string file_name);

  const std::string palette_file();
  const std::string frame_file();
  const std::string frame_symbolic_file();
  const std::string layer_file();
  const std::string layer_symbolic_file();
  const std::string chroma_file();
  const std::string chroma_symbolic_file();
  const std::string grid_file();
  const std::string grid_symbolic_file();

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

    return YAML::convert<GLOW_STRUCT>::decode(node, glow_struct);
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
} // namespace glow
