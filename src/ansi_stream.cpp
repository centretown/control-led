#include "ansi_stream.h"

namespace glow
{
  const std::string bullet = "\U000025CF";

  const std::string escape = "\x1b";
  const std::string escape_end = escape + "[0m";
  const std::string escape_hide_cursor = escape + "[?25l";
  const std::string escape_show_cursor = escape + "[?25h";
  const std::string escape_at = escape + "[";
  const std::string escape_clear_from_cursor = escape + "[0J";
  const std::string escape_set_color = escape + "[38;2;";

  void ansi_set_color(Color color, std::ostream &stream)
  {
    stream << escape_set_color
           << (uint16_t)color.red << ';'
           << (uint16_t)color.green << ';'
           << (uint16_t)color.blue << 'm';
  }

  void ansi_print_fixed(uint16_t width, std::string text, Color color, std::ostream &stream)
  {
    ansi_set_color(color, stream);
    stream << std::setw(width) << std::left << text;
    stream << escape_end;
  }

  void ansi_print(std::string text, Color color, std::ostream &stream)
  {
    ansi_set_color(color, stream);
    stream << text << escape_end;
  }

  void ansi_print_line(std::string text, Color color, std::ostream &stream)
  {
    ansi_print(text, color, stream);
    stream << '\n';
  }

  void ansi_at(uint16_t row, uint16_t column, std::ostream &stream)
  {
    stream << escape_at
           << row + 1 << ';'
           << column + 1 << 'H'
           << escape_end;
  }

  void ansi_hide_cursor(std::ostream &stream)
  {
    stream << escape_hide_cursor << escape_end;
  }

  void ansi_show_cursor(std::ostream &stream)
  {
    stream << escape_show_cursor << escape_end;
  }

  void ansi_clear_from_cursor(std::ostream &stream)
  {
    stream << escape_clear_from_cursor << escape_end;
  }

  void ansi_print_at(std::string text, uint16_t row, uint16_t column, Color color, std::ostream &stream)
  {
    ansi_at(row, column, stream);
    ansi_set_color(color, stream);
    stream << text << escape_end;
  }

  void ansi_put_light(uint16_t row, uint16_t column, Color color, std::ostream &stream)
  {
    ansi_at(row, 2 * column, stream);
    ansi_set_color(color, stream);
    stream << bullet << ' ' << escape_end;
  }
}
