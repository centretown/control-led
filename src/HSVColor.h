#pragma once
#include <unordered_map>

#ifndef STRIP_YAML
#include <yaml-cpp/yaml.h>
#endif

#include "base.h"
#include "esphome/core/color.h"
#include "esphome/components/light/esp_hsv_color.h"

using esphome::Color;
using esphome::light::ESPHSVColor;

namespace glow
{
  constexpr uint16_t byte_limit = 0xff;
  constexpr uint16_t hue_segment_count = 6;
  constexpr uint16_t hue_limit = byte_limit * hue_segment_count;
  constexpr uint16_t hue_segment = hue_limit / hue_segment_count;

  constexpr uint16_t hue_red = 0;
  constexpr uint16_t hue_yellow = hue_segment;
  constexpr uint16_t hue_green = hue_limit * 2 / hue_segment_count;
  constexpr uint16_t hue_cyan = hue_limit * 3 / hue_segment_count;
  constexpr uint16_t hue_blue = hue_limit * 4 / hue_segment_count;
  constexpr uint16_t hue_magenta = hue_limit * 5 / hue_segment_count;

  enum : uint8_t
  {
    RED,
    GREEN,
    BLUE,
  };

  struct HSVColor
  {
    union
    {
      struct
      {
        uint16_t hue;
        uint8_t saturation;
        uint8_t value;
      };

      uint32_t raw_32 = 0;
    };

    bool setup()
    {
      return true;
    }

    ESPHSVColor to_esp_hsv_color() const ALWAYS_INLINE
    {
      return ESPHSVColor(hue / hue_segment_count, saturation, value);
    }

    void from_esp_hsv_color(ESPHSVColor esph_hsv)
    {
      hue = esph_hsv.hue * hue_segment_count;
      saturation = esph_hsv.saturation;
      value = esph_hsv.value;
    }

    Color to_rgb();

    void from_rgb(Color color);

    void to_color_wheel(float &f_hue, float &f_saturation, float &f_value) const
    {
      f_hue = round(static_cast<float>(hue) * 360.0f /
                    static_cast<float>(hue_limit));
      f_saturation = round(static_cast<float>(saturation) * 100.0f /
                           static_cast<float>(byte_limit));
      f_value = round(static_cast<float>(value) * 100.0f /
                      static_cast<float>(byte_limit));
    }

    void from_color_wheel(float f_hue, float f_saturation, float f_value)
    {
      f_hue = round(f_hue);
      f_saturation = round(f_saturation);
      f_value = round(f_value);

      hue = static_cast<uint16_t>(f_hue / 360.0f *
                                  static_cast<float>(hue_limit));
      saturation = static_cast<uint8_t>(f_saturation / 100.0f *
                                        static_cast<float>(byte_limit));
      value = static_cast<uint8_t>(f_value / 100.0f *
                                   static_cast<float>(byte_limit));
    }

    enum : uint8_t
    {
      HUE,
      SATURATION,
      VALUE,
      KEY_COUNT,
    };

    static std::string keys[KEY_COUNT];
    static std::string rgb_keys[3];
  };
}

#ifndef STRIP_YAML
namespace YAML
{
  using glow::BLUE;
  using glow::GREEN;
  using glow::RED;

  using glow::HSVColor;

  template <>
  struct convert<HSVColor>
  {
    static Node encode(const HSVColor &hsv)
    {
      Node node;
      float f_hue, f_saturation, f_value;
      hsv.to_color_wheel(f_hue, f_saturation, f_value);
      node[HSVColor::keys[HSVColor::HUE]] = f_hue;
      node[HSVColor::keys[HSVColor::SATURATION]] = f_saturation;
      node[HSVColor::keys[HSVColor::VALUE]] = f_value;
      return node;
    }

    static bool decode(const Node &node, HSVColor &hsv)
    {
      if (!node.IsMap())
      {
        hsv.setup();
        return false;
      }

      float f_hue = 0.0;
      float f_saturation = 0.0;
      float f_value = 0.0;

      for (auto key = 0; key < HSVColor::KEY_COUNT; ++key)
      {
        Node item = node[HSVColor::keys[key]];
        if (!item.IsDefined())
        {
          continue;
        }

        switch (key)
        {
        case HSVColor::HUE:
          f_hue = item.as<float>();
          break;
        case HSVColor::SATURATION:
          f_saturation = item.as<float>();
          break;
        case HSVColor::VALUE:
          f_value = item.as<float>();
          break;
        }
      }

      hsv.from_color_wheel(f_hue, f_saturation, f_value);
      return true;
    }
  };

  template <>
  struct convert<Color>
  {
    static Node encode(const Color &color)
    {
      Node node;
      node[HSVColor::rgb_keys[RED]] = static_cast<uint16_t>(color.red);
      node[HSVColor::rgb_keys[GREEN]] = static_cast<uint16_t>(color.green);
      node[HSVColor::rgb_keys[BLUE]] = static_cast<uint16_t>(color.blue);
      return node;
    }

    static bool decode(const Node &node, Color &color)
    {
      if (!node.IsMap())
      {
        return false;
      }
      color.red = node[HSVColor::rgb_keys[RED]].as<uint8_t>();
      color.green = node[HSVColor::rgb_keys[GREEN]].as<uint8_t>();
      color.blue = node[HSVColor::rgb_keys[BLUE]].as<uint8_t>();
      return true;
    }
  };
}
#endif