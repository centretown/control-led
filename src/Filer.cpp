#include "Filer.h"
#include <ranges>

namespace glow
{
  std::error_code err;
#ifdef DATA_DIR
  std::filesystem::path data_directory = std::filesystem::weakly_canonical(DATA_DIR, err);
#else
  std::filesystem::path data_directory = std::filesystem::weakly_canonical("", err);
#endif
  const std::string palettes = "palettes";
  const std::string frames = "frames";
  const std::string layers = "layers";
  const std::string chromas = "chromas";
  const std::string grids = "grids";
  const std::string base = "base";
  const std::string derived = "derived";
  const std::string extension = ".yaml";
  const std::string palette_name = "palette";

  const std::string catalog = "catalog";
  const std::string generated = "generated";
  const std::string header_name = "catalog.h";
  const std::string source_name = "catalog.cpp";

  const std::string extend(const std::string name)
  {
    return name + extension;
  }

  const std::string catalog_file(const std::string name)
  {
    return data_directory / catalog / extend(name);
  }

  const std::string catalog_directory()
  {
    return data_directory / catalog;
  }
  
  const std::string generated_directory()
  {
    return data_directory / generated;
  }
  
  const std::string source_file()
  {
    return data_directory / generated / source_name;
  }
  
  const std::string header_file()
  {
    return data_directory / generated / header_name;
  }

  const std::string effect_file(std::string name)
  {
    return data_directory / generated / name;
  }

  const std::string palette_file()
  {
    return data_directory / palettes / extend(palette_name);
  }

  const std::string palette_file(const std::string name)
  {
    return data_directory / palettes / extend(name);
  }

  const std::string derived_frame(const std::string name)
  {
    return data_directory / frames / derived / extend(name);
  }

  const std::string custom_frame(const std::string name)
  {
    return data_directory / frames / extend(name);
  }

  const std::string derived_layer(const std::string name)
  {
    return data_directory / layers / derived / extend(name);
  }

  const std::string custom_layer(const std::string name)
  {
    return data_directory / layers / extend(name);
  }

  const std::string derived_chroma(const std::string name)
  {
    return data_directory / chromas / derived / extend(name);
  }

  const std::string custom_chroma(const std::string name)
  {
    return data_directory / chromas / extend(name);
  }

  const std::string derived_grid(const std::string name)
  {
    return data_directory / grids / derived / extend(name);
  }

  const std::string custom_grid(const std::string name)
  {
    return data_directory / grids / extend(name);
  }

  bool catalog_copy(std::vector<std::string> frame_names, std::string &message)
  {
    bool status = true;
    std::stringstream s;

    std::filesystem::copy_options options =
        std::filesystem::copy_options::overwrite_existing;

    std::error_code err;

    for (auto frame_name : frame_names)
    {
      if (std::filesystem::copy_file(custom_frame(frame_name),
                                     catalog_file(frame_name),
                                     options, err) ==
          false)
      {
        s << "Failed to copy " << '"' << frame_name << '"' << ": ";
        s << err.message() << "! ";
        status = false;
      }
      else
      {
        s << "Copied " << '"' << frame_name << '"' << ". ";
      }
    }

    message = s.str();
    return status;
  }

  bool file_system_create(std::string path, std::string &message)
  {
    bool status = true;
    std::stringstream s;
    set_data_path(path);
    std::error_code err;
    auto create = [&](std::string name)
    {
      if (std::filesystem::create_directories(name, err) == false)
      {
        s << "Failed to create_directory "
          << '"' << name << '"' << "! "
          << err.message() << ". ";
        message = s.str();
        status = false;
      }
    };

    create(data_directory / palettes);
    create(data_directory / frames / derived);
    create(data_directory / layers / derived);
    create(data_directory / grids / derived);
    create(data_directory / chromas / derived);
    create(data_directory / catalog);
    create(data_directory / generated);

    return status;
  }

  bool file_system_exists(std::string path)
  {
    return std::filesystem::exists(path);
  }

  const std::string data_path()
  {
    return data_directory / "";
  }

  const std::string set_data_path(std::string path)
  {
    std::error_code err;
    data_directory = std::filesystem::weakly_canonical(path, err);
    return data_path();
  }
}