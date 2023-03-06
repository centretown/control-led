#include "build_catalog.h"

namespace glow
{
  std::map<std::string, Frame> catalog_items;

  void add_frame_to_catalog(std::string name, Frame &frame)
  {
    catalog_items[name] = frame;
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

  void generate_source(std::ostream &source)
  {
    source << "#include \"catalog.h\"\n"
              "namespace glow {\n"
              "const char *catalog_names[FRAME_COUNT] = {\n";
    for (auto catalog_item : catalog_items)
    {
      source << "\"" << catalog_item.first << "\",\n";
    }
    source << "};\n";

    source << "Frame catalog[FRAME_COUNT]= {\n";
    for (auto catalog_item : catalog_items)
    {
      source << catalog_item.second.make_code() << ",\n";
    }
    source << "};\n";

    source << "Frame &from_catalog(CATALOG_INDEX index)"
              "{return catalog[index%FRAME_COUNT];}\n";

    source << "const char *catalog_name(CATALOG_INDEX index)"
              "{return catalog_names[index%FRAME_COUNT];}\n";

    source << "} // namespace glow\n";
  }

  void generate_header(std::ostream &header)
  {
    header << "#pragma once\n"
              "#include \"Frame.h\"\n"
              "namespace glow {\n";

    header << "enum CATALOG_INDEX : uint8_t {\n";
    for (auto catalog_item : catalog_items)
    {
      header << make_constant_name(catalog_item.first) << ",\n";
    }
    header << "FRAME_COUNT,\n"
              "};\n";

    header << "extern const char *catalog_names[FRAME_COUNT];\n"
              "extern Frame catalog[FRAME_COUNT];\n"
              "extern Frame &from_catalog(CATALOG_INDEX index);\n"
              "extern const char *catalog_name(CATALOG_INDEX index);\n"
              "} // namespace glow\n";
  }

  bool make_catalog_code()
  {
    std::string caution = "// CAUTION GENERATED FILE\n";
    std::fstream header, source;

    header.open(header_file(), std::fstream::out);
    if (header.bad())
    {
      return false;
    }
    header << caution;
    generate_header(header);
    header.close();

    source.open(source_file(), std::fstream::out);
    if (source.bad())
    {
      return false;
    }
    source << caution;
    generate_source(source);
    source.close();

    return true;
  }

  bool make_catalog_effects(std::string name, uint16_t rows, uint32_t interval)
  {
    std::fstream effects;
    effects.open(name, std::fstream::out);
    if (effects.bad())
    {
      return false;
    }

    for (auto catalog_item : catalog_items)
    {
      std::string id_name = make_constant_name(catalog_item.first);
      effects << "- addressable_lambda: " << '\n';
      effects << "    name: \"" << catalog_item.first << "\"" << '\n';
      effects << "    update_interval: 48ms" << '\n';
      effects << "    lambda: |-" << '\n';
      effects << "      #include \"glow/catalog.h\"" << '\n';
      effects << "      static glow::Frame frame(glow::from_catalog(glow::" << id_name << "));" << '\n';
      effects << "      if (initial_run) {" << '\n';
      effects << "        frame.setup(it.size(), " << rows << ", " << interval << ");" << '\n';
      effects << "      }" << '\n';
      effects << "      if (frame.is_ready()) {" << '\n';
      effects << "        frame.spin(it);" << '\n';
      effects << "      }" << '\n';
    }
    effects.close();
    return true;
  }

} // namespace glow
