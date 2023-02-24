#include "build_catalog.h"

namespace glow
{
  std::map<std::string, Frame> items;

  void add_frame_to_catalog(std::string name, Frame &frame)
  {
    items[name] = frame;
  }

  std::string make_constant_name(std::string src)
  {
    std::string upper;
    for (auto c : src)
    {
      switch (c)
      {
      case ',':
      case '-':
      case ' ':
        c = '_';
        break;
      default:
        c = toupper(c);
        break;
      }
      upper += c;
    }
    return upper;
  };

  std::string make_code_from_catalog(std::string name)
  {
    std::stringstream header;
    std::stringstream source;
    generate_code_to_streams(header, source);
    header << source.str();
    return header.str();
  }

  bool make_files_from_catalog()
  {
    std::fstream header, source;
    header.open(header_file(), std::fstream::out);
    if (header.bad())
    {
      return false;
    }
    source.open(source_file(), std::fstream::out);
    if (source.bad())
    {
      return false;
    }

    generate_code_to_streams(header, source);

    header.close();
    source.close();
    return true;
  }

} // namespace glow
