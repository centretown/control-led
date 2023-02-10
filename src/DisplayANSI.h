#pragma once
#include <iostream>
#include <string>

#include "base.h"
#include "esphome/core/color.h"
using esphome::Color;

namespace glow
{
  const std::string bullet = "\U000025CF";

  const std::string escape = "\x1b";
  const std::string ansi_end = escape + "[0m";
  const std::string ansi_hide_cursor = escape + "[?25l";
  const std::string ansi_show_cursor = escape + "[?25h";
  const std::string ansi_at = escape + "[";
  const std::string ansi_clear_from_cursor = escape + "[0J";
  const std::string ansi_set_color = escape + "[38;2;";

  class DisplayANSI
  {
  private:
    std::string element = bullet;
    uint16_t width = 2;

  public:
    static void set_color(Color color) ALWAYS_INLINE
    {
      std::cout << ansi_set_color
                << (uint16_t)color.red << ';'
                << (uint16_t)color.green << ';'
                << (uint16_t)color.blue << 'm';
    }

    static void print_line(std::string text, Color color) ALWAYS_INLINE
    {
      set_color(color);
      std::cout << text << ansi_end << '\n';
    }

    static void at(uint16_t row, uint16_t column) ALWAYS_INLINE
    {
      std::cout << ansi_at << row << ';' << column << 'H' << ansi_end;
    }

    static void hide_cursor() ALWAYS_INLINE
    {
      std::cout << ansi_hide_cursor << ansi_end;
      // printf("\x1b[?25l\x1b[0m");
    }

    static void show_cursor() ALWAYS_INLINE
    {
      std::cout << ansi_show_cursor << ansi_end;
      // printf("\x1b[?25h\x1b[0m");
    }

    static void clear_from_cursor() ALWAYS_INLINE
    {
      std::cout << ansi_clear_from_cursor << ansi_end;
      // printf("\x1b[0J\x1b[0m");
    }

  public:
    // void present(uint16_t row, uint16_t column, Color color) ALWAYS_INLINE
    // {
    //   at(row + 1, (column + 1) * width);
    //   printf("\x1b[38;2;%d;%d;%dm%s \x1b[0m",
    //          color.r, color.g, color.b, element);
    // }

    // void setup(const char *el = nullptr, uint16_t w = 2)
    // {
    //   width = w;
    //   if (el != nullptr)
    //   {
    //     strncpy(element, el, sizeof(element));
    //   }
    //   at(1, 1);
    //   clear_from_cursor();
    //   hide_cursor();
    // }
  };
}
