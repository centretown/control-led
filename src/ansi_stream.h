#pragma once
#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

#include "base.h"
#include "RGBColor.h"
// #include "esphome/core/color.h"
// using esphome::Color;

namespace glow
{
  extern void ansi_set_color(Color color, std::ostream &stream);
  extern void ansi_print(std::string text, Color color, std::ostream &stream);
  extern void ansi_print_line(std::string text, Color color, std::ostream &stream);
  extern void ansi_at(uint16_t row, uint16_t column, std::ostream &stream);
  extern void ansi_hide_cursor(std::ostream &stream);
  extern void ansi_show_cursor(std::ostream &stream);
  extern void ansi_clear_from_cursor(std::ostream &stream);
  extern void ansi_print_at(std::string text, uint16_t row, uint16_t column, Color color, std::ostream &stream);
  extern void ansi_put_light(uint16_t row, uint16_t column, Color color, std::ostream &stream);
  extern void ansi_print_fixed(uint16_t width, std::string text, Color color, std::ostream &stream);
}
