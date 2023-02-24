#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <yaml-cpp/yaml.h>

namespace glow
{
  const std::string data_path();
  const std::string set_data_path(std::string path);
  const std::filesystem::path data_path(std::string file_name);
  bool file_system_exists(std::string path);
  bool file_system_create(std::string path, std::string &message);

  const std::string palette_file();
  const std::string derived_frame(std::string name);
  const std::string custom_frame(std::string name);
  const std::string derived_layer(std::string name);
  const std::string custom_layer(std::string name);
  const std::string derived_chroma(std::string name);
  const std::string custom_chroma(std::string name);
  const std::string derived_grid(std::string name);
  const std::string custom_grid(std::string name);

  const std::string catalog_file(const std::string name);
  const std::string catalog_directory();
  const std::string source_file();
  const std::string header_file();

  const std::string generated_directory();

  bool catalog_copy(std::vector<std::string> frame_names, std::string &message);

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
