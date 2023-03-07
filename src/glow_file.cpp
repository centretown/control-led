#include "glow_file.h"
#include "build_catalog.h"

bool file_load_frame(std::string frame_name, glow::Frame &frame, std::string &message)
{
  std::stringstream s;
  std::string frame_file = glow::custom_frame(frame_name);

  if (glow::load_yaml(frame_file, frame) == false)
  {
    s << "Unable to load " << frame_file;
    message = s.str();
    return false;
  }

  s << "Loaded frame " << frame_file;
  message = s.str();
  return true;
}

bool file_load_palette(std::string &message)
{
  std::stringstream s;
  std::string palette_file = glow::palette_file();

  if (glow::Chroma::load_palette(palette_file) == false)
  {
    s << "Unable to load " << palette_file;
    message = s.str();
    return false;
  }

  s << "Loaded palette " << palette_file;
  message = s.str();
  return true;
}

const std::string file_system_path()
{
  return glow::data_path();
}

bool file_system_exists(std::string data_path)
{
  if (glow::file_system_exists(data_path))
  {
    glow::set_data_path(data_path);
    return true;
  }
  return false;
}

bool file_system_create(std::string data_path, std::string &message)
{
  std::stringstream s;

  if (glow::file_system_create(data_path, message) ==
      false)
  {
    return false;
  }

  s << "File system created at " << '"' << glow::data_path() << '"';
  message = s.str();
  return true;
}

bool file_catalog_copy(std::vector<std::string> frame_names, std::string &message)
{
  return glow::catalog_copy(frame_names, message);
}

void file_catalog_list(std::vector<std::string> &frame_names)
{
  for (auto const &entry : std::filesystem::directory_iterator{glow::catalog_directory()})
  {
    frame_names.push_back(entry.path().stem());
  }
}

std::vector<std::string> source_files = {
    "base.h",
    "catalog.cpp",
    "catalog.h",
    "Chroma.cpp",
    "Chroma.h",
    "Frame.cpp",
    "Frame.h",
    "Grid.cpp",
    "Grid.h",
    "HSVColor.cpp",
    "HSVColor.h",
    "Layer.cpp",
    "Layer.h",
    "Light.h",
    "RGBColor.cpp",
    "RGBColor.h",
};

std::vector<glow_config> config_files = {
    {"strip_effects.yml", 1, 48},
    {"grid_effects.yml", 4, 48},
};

// void file_catalog_build(
//     std::string code_path,
//     std::string target_path,
//     std::string &message)
void file_catalog_build(std::string &message)
{
  std::vector<std::string> frame_names;
  file_catalog_list(frame_names);

  for (auto &frame_name : frame_names)
  {
    glow::Frame frame;
    load_yaml(glow::catalog_file(frame_name), frame);
    add_frame_to_catalog(frame_name, frame);
  }

  glow::make_catalog_code();

  for (auto &c : config_files)
  {
    glow::make_catalog_effects(
        glow::effect_file(c.file_name), c.rows, c.interval);
  }

  message = "Source code in " + glow::generated_directory();
}
