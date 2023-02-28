#include "glow_show.h"

void show_normal(uint16_t row)
{
  glow::ansi_at(row, 0, std::cout);
  glow::ansi_show_cursor(std::cout);
}

bool show_lights(uint16_t length, uint16_t rows, uint32_t interval,
                 std::string frame_name, std::string &message)
{
  std::stringstream s;
  glow::HostLight light;
  if (light.setup(length, rows) ==
      false)
  {
    s << "show: light setup failed length: " << length
      << " ,rows: " << rows;
    message = s.str();
    return false;
  }

  glow::Frame frame;
  if (file_load_frame(frame_name, frame, message) ==
      false)
  {
    return false;
  }

  if (frame.setup(length, rows, interval) ==
      false)
  {
    s << "frame setup failed! length: " << frame.get_length()
      << " ,rows: " << frame.get_rows()
      << " ,interval: " << frame.get_interval();
    message = s.str();
    return false;
  }

  glow::ansi_at(0, 0, std::cout);
  glow::ansi_clear_from_cursor(std::cout);
  glow::ansi_hide_cursor(std::cout);

  for (;;)
  {
    frame.spin(&light);
    std::this_thread::sleep_for(std::chrono::milliseconds(frame.get_interval()));
  }

  return true;
}

void show_palette(uint16_t columns, uint16_t column_width, bool by_hue)
{
  if (by_hue)
  {
    glow::Chroma::palette.print_by_hue(columns, column_width, std::cout);
  }
  else
  {
    glow::Chroma::palette.print(columns, column_width, std::cout);
  }
}

void show_frame(glow::Frame &frame)
{
  YAML::Node node_out = YAML::convert<glow::Frame>::encode(frame);
  YAML::Emitter out;
  out << node_out;
  std::cout << out.c_str();
}
