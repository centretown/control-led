#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include "Frame.h"
#include "Filer.h"

namespace glow
{
  extern std::map<std::string, Frame> items;

  extern void add_frame_to_catalog(std::string name, Frame &frame);

  extern std::string make_code_from_catalog(std::string name);

  extern bool make_files_from_catalog();

  extern std::string make_constant_name(std::string src);

  template <typename STREAM_OUT>
  void generate_header(STREAM_OUT &header)
  {
    header << "#pragma once\n"
           << "#include \"Frame.h\"\n"
              "namespace glow {\n";

    header << "enum LIBRARY_INDEX : uint8_t {\n";
    for (auto pair : items)
    {
      header << make_constant_name(pair.first) << ",\n";
    }

    // terminate enum
    header << "FRAME_COUNT,\n";
    header << "};\n";
    header << "extern const char *catalog_names[FRAME_COUNT];\n";
    header << "extern Frame catalog[FRAME_COUNT];\n";
    header << "extern Frame &from_catalog(LIBRARY_INDEX index);\n";
    header << "extern const char *catalog_name(LIBRARY_INDEX index);\n";

    header << "} // namespace glow\n";
  }

  template <typename STREAM_OUT>
  void generate_source(STREAM_OUT &source)
  {
    source << "#include \"catalog.h\"\n"
           << "namespace glow {\n";

    source << "const char *catalog_names[FRAME_COUNT] = {\n";
    for (auto pair : items)
    {
      source << "\"" << pair.first << "\",\n";
    }
    source << "};\n";

    source << "Frame catalog[FRAME_COUNT]= {\n";
    for (auto pair : items)
    {
      source << pair.second.make_code() << ",\n";
    }

    // terminate array
    source << "};\n";

    // create functions
    source << "Frame &from_catalog(LIBRARY_INDEX index){return catalog[index%FRAME_COUNT];}\n";
    source << "const char *catalog_name(LIBRARY_INDEX index){return catalog_names[index%FRAME_COUNT];}\n";

    // terminate namespace
    source << "} // namespace glow\n";
  }

  template <typename STREAM_OUT>
  bool generate_code_to_streams(STREAM_OUT &header, STREAM_OUT &source)
  {
    std::string caution = "// CAUTION GENERATED FILE\n";

    header << caution;
    generate_header(header);

    source << caution;
    generate_source(source);

    return true;
  }

} // namespace glow
