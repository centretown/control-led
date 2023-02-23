#include "Filer.h"

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
  const std::string header_name = "library.h";
  const std::string source_name = "library.cpp";

  const std::string extend(const std::string name)
  {
    return name + extension;
  }

  const std::string catalog_file(const std::string name)
  {
    return data_directory / catalog / extend(name);
  }
  const std::string source_file()
  {
    return data_directory / generated / source_name;
  }
  const std::string header_file()
  {
    return data_directory / generated / header_name;
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

  bool create_directory(std::string directory_name)
  {
    if (!std::filesystem::exists(data_path()))
    {
      std::error_code err;
      bool status = std::filesystem::create_directory(data_path(), err);
      if (status == false)
      {
        return false;
      }
    }
    return true;
  }

  bool make_file_system()
  {
    std::error_code err;
    auto create = [&](std::string name)
    {
      if (std::filesystem::create_directories(name, err) == false)
      {
        std::cout << "Filer::Unable to create_directory "
                  << name << '\n'
                  << err.message() << '\n';
      }
    };

    create(data_directory / palettes);
    create(data_directory / frames / derived);
    create(data_directory / layers / derived);
    create(data_directory / grids / derived);
    create(data_directory / chromas / derived);
    create(data_directory / catalog);
    create(data_directory / generated);

    return true;
  }

  bool file_system_exists()
  {
    return std::filesystem::exists(data_path());
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