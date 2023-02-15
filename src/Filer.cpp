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

  const std::string palette_name = "palette.yaml";
  
  const std::string palette_file()
  {
    return data_directory / palettes / palette_name;
  }

  const std::string palette_file(const std::string palette_name)
  {
    return data_directory / palettes / palette_name;
  }

  const std::string derived_frame(const std::string name)
  {
    return data_directory / frames / derived / name;
  }

  const std::string custom_frame(const std::string name)
  {
    return data_directory / frames / custom / name;
  }

  const std::string derived_layer(const std::string name)
  {
    return data_directory / layers / derived / name;
  }

  const std::string custom_layer(const std::string name)
  {
    return data_directory / layers / custom / name;
  }

  const std::string derived_chroma(const std::string name)
  {
    return data_directory / chromas / derived / name;
  }

  const std::string custom_chroma(const std::string name)
  {
    return data_directory / chromas / custom / name;
  }

  const std::string derived_grid(const std::string name)
  {
    return data_directory / grids / derived / name;
  }

  const std::string custom_grid(const std::string name)
  {
    return data_directory / grids / custom / name;
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

    if (!create_directory(data_directory))
    {
      return false;
    }

    if (!create_directory(data_directory / palettes))
    {
      return false;
    }

    if (!create_directory(data_directory / frames))
    {
      return false;
    }
    if (!create_directory(data_directory / frames / custom))
    {
      return false;
    }
    if (!create_directory(data_directory / frames / derived))
    {
      return false;
    }

    if (!create_directory(data_directory / layers))
    {
      return false;
    }
    if (!create_directory(data_directory / layers / custom))
    {
      return false;
    }
    if (!create_directory(data_directory / layers / derived))
    {
      return false;
    }

    if (!create_directory(data_directory / grids))
    {
      return false;
    }
    if (!create_directory(data_directory / grids / custom))
    {
      return false;
    }
    if (!create_directory(data_directory / grids / derived))
    {
      return false;
    }

    if (!create_directory(data_directory / chromas))
    {
      return false;
    }
    if (!create_directory(data_directory / chromas / custom))
    {
      return false;
    }
    if (!create_directory(data_directory / chromas / derived))
    {
      return false;
    }

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