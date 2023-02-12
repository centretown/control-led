#include "Filer.h"

namespace glow
{
#ifdef DATA_DIR
  std::filesystem::path data_directory(DATA_DIR);
#else
  std::filesystem::path data_directory;
#endif

  const std::string palette_name = "palettes/palette.yaml";
  const std::string frame_name = "frames/frame.yaml";
  const std::string frame_symbolic = "frames/frame_symbolic.yaml";
  const std::string layer_name = "layers/layer.yaml";
  const std::string layer_symbolic = "layers/layer_symbolic.yaml";
  const std::string grid_name = "grids/grid.yaml";
  const std::string grid_symbolic = "grids/grid_symbolic.yaml";
  const std::string chroma_name = "chromas/chroma.yaml";
  const std::string chroma_symbolic = "chromas/chroma_symbolic.yaml";

  const std::string palette_file()
  {
    return data_path() + palette_name;
  }

  const std::string frame_file()
  {
    return data_path() + frame_name;
  }
  const std::string frame_symbolic_file()
  {
    return data_path() + frame_symbolic;
  }

  const std::string layer_file()
  {
    return data_path() + layer_name;
  }

  const std::string layer_symbolic_file()
  {
    return data_path() + layer_symbolic;
  }

  const std::string chroma_file()
  {
    return data_path() + chroma_name;
  }

  const std::string chroma_symbolic_file()
  {
    return data_path() + chroma_symbolic;
  }

  const std::string grid_file()
  {
    return data_path() + grid_name;
  }

  const std::string grid_symbolic_file()
  {
    return data_path() + grid_symbolic;
  }

  const std::string data_path()
  {
    return data_directory / "";
    // if (data_directory != "" && data_directory.back() != '/')
    // {
    //   data_directory.append("/");
    // }
    // return data_directory;
  }

  std::string data_path(std::string file_name)
  {
    std::filesystem::path append = data_directory / file_name;
    return append.c_str();
  }

  const std::string set_data_path(std::string path)
  {
    data_directory = path;
    return data_path();
  }
}