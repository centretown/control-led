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
  bool file_system_exists();
  bool make_file_system();

  const std::string palette_file();
  const std::string frame_file();
  const std::string frame_symbolic_file();
  const std::string layer_file();
  const std::string layer_symbolic_file(std::string name);
  const std::string layer_symbolic_file();
  const std::string chroma_file();
  const std::string chroma_symbolic_file();
  const std::string grid_file();
  const std::string grid_symbolic_file();

  // extern std::filesystem::path data_directory;
  // extern const std::string palettes;
  // extern const std::string frames;
  // extern const std::string layers;
  // extern const std::string chromas;
  // extern const std::string grids;
  // extern const std::string symbols;
  // extern const std::string derived;
  // extern const std::string palette_name;
  // extern const std::string frame_name;
  // extern const std::string frame_symbolic;
  // extern const std::string layer_name;
  // extern const std::string layer_symbolic;
  // extern const std::string grid_name;
  // extern const std::string grid_symbolic;
  // extern const std::string chroma_name;
  // extern const std::string chroma_symbolic;

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
