#include "Filer.h"

namespace glow
{
#ifdef DATA_DIR
  std::filesystem::path data_directory(DATA_DIR);
#else
  std::filesystem::path data_directory;
#endif

  const std::string palettes = "palettes";
  const std::string frames = "frames";
  const std::string layers = "layers";
  const std::string chromas = "chromas";
  const std::string grids = "grids";
  const std::string base = "base";
  const std::string custom = "custom";
  const std::string derived = "derived";
  const std::string extension = ".yaml";
  const std::string palette_name = "palette";

  const std::string extend(const std::string name)
  {
    return name + extension;
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
    return data_directory / frames / custom / extend(name);
  }

  const std::string derived_layer(const std::string name)
  {
    return data_directory / layers / derived / extend(name);
  }

  const std::string custom_layer(const std::string name)
  {
    return data_directory / layers / custom / extend(name);
  }

  const std::string derived_chroma(const std::string name)
  {
    return data_directory / chromas / derived / extend(name);
  }

  const std::string custom_chroma(const std::string name)
  {
    return data_directory / chromas / custom / extend(name);
  }

  const std::string derived_grid(const std::string name)
  {
    return data_directory / grids / derived / extend(name);
  }

  const std::string custom_grid(const std::string name)
  {
    return data_directory / grids / custom / extend(name);
  }

  const std::string data_path()
  {
    return data_directory / "";
  }

  bool create_directory(std::string directory_name)
  {
    if (!std::filesystem::exists(data_directory))
    {
      std::error_code err;
      bool status = std::filesystem::create_directory(data_directory, err);
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
    create(data_directory / frames / custom);
    create(data_directory / frames / derived);
    create(data_directory / layers / custom);
    create(data_directory / layers / derived);
    create(data_directory / grids / custom);
    create(data_directory / grids / derived);
    create(data_directory / chromas / custom);
    create(data_directory / chromas / derived);
    return true;
  }

  bool file_system_exists()
  {
    if (!std::filesystem::exists(data_directory))
    {
      return false;
    }
    return true;
  }

  const std::string set_data_path(std::string path)
  {

    data_directory = path;
    return data_path();
  }
}