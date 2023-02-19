#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include "Frame.h"

namespace glow
{
  extern std::map<std::string, Frame> items;

  extern void add_frame_to_library(std::string name, Frame &frame);

  extern std::string make_code_from_library(std::string name);

  extern bool make_files_from_library(std::string name);

  extern std::string make_constant_name(std::string src);

  template <typename STREAM_OUT>
  bool generate_code_to_streams(std::string name, STREAM_OUT &header, STREAM_OUT &source)
  {
    std::string caution = "// CAUTION GENERATED FILE\n";

    header << caution;
    source << caution;

    header << "#pragma once\n"
           << "#include \"Frame.h\"\n"
              "namespace glow {\n";

    header << "enum LIBRARY_INDEX : uint8_t {\n";

    source << "#include \"" << name << ".h\"\n"
           << "namespace glow {\n";

    source << "Frame library[FRAME_COUNT] = {\n";

    uint index = 0;
    for (auto pair : items)
    {
      header << make_constant_name(pair.first) << ",\n";
      source
          << pair.second.make_code() << ",\n";
      ++index;
    }

    // terminate enum
    header << "FRAME_COUNT,\n";
    header << "};\n";
    header << "extern Frame library[FRAME_COUNT];\n";
    header << "extern Frame &from_library(LIBRARY_INDEX index);\n"
           << "} // namespace glow\n";

    // terminate array
    source << "};\n"
           << "Frame &from_library(LIBRARY_INDEX index){return library[index%FRAME_COUNT];}\n"
           << "} // namespace glow\n";

    return true;
  }

} // namespace glow
