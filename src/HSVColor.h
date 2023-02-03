#pragma once

#include <yaml-cpp/yaml.h>

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
    HUE,
    SATURATION,
    VALUE,
  };
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
      uint32_t raw_32;
    };

    HSVColor(uint32_t raw_32 = 0) ALWAYS_INLINE : raw_32(raw_32) {}

    HSVColor(float f_hue, float f_saturation, float f_value);

    HSVColor(uint16_t hue, uint8_t saturation, uint8_t value) ALWAYS_INLINE
        : hue(hue),
          saturation(saturation),
          value(value) {}

    HSVColor(ESPHSVColor esph_hsv) ALWAYS_INLINE
    {
      from_esp_hsv_color(esph_hsv);
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
      f_hue = static_cast<float>(hue) * 360 /
              static_cast<float>(hue_limit);
      f_saturation = static_cast<float>(saturation) * 100.0 /
                     static_cast<float>(byte_limit);
      f_value = static_cast<float>(value) * 100.0 /
                static_cast<float>(byte_limit);
    }

    void from_color_wheel(float f_hue, float f_saturation, float f_value)
    {
      hue = static_cast<uint16_t>(f_hue / 360.0 *
                                  static_cast<float>(hue_limit));
      saturation = static_cast<uint8_t>(f_saturation / 100.0 *
                                        static_cast<float>(byte_limit));
      value = static_cast<uint8_t>(f_value / 100.0 *
                                   static_cast<float>(byte_limit));
    }

    friend bool operator==(const HSVColor &a, const HSVColor &b) ALWAYS_INLINE
    {
      return (a.raw_32 == b.raw_32);
    }

    static std::string hsv_keys[3];
    static std::string rgb_keys[3];
  };

  // ESPHSVColor color_to_hsv(Color color);
  // uint32_t hsv_to_u32(ESPHSVColor hsv);
  // ESPHSVColor u32_to_hsv(uint32_t hsv32);

}

namespace YAML
{
  using glow::BLUE;
  using glow::GREEN;
  using glow::HUE;
  using glow::RED;
  using glow::SATURATION;
  using glow::VALUE;

  using glow::HSVColor;

  template <>
  struct convert<HSVColor>
  {
    static Node encode(const HSVColor &hsv)
    {
      Node node;
      float f_hue, f_saturation, f_value;
      hsv.to_color_wheel(f_hue, f_saturation, f_value);
      node[HSVColor::hsv_keys[HUE]] = f_hue;
      node[HSVColor::hsv_keys[SATURATION]] = f_saturation;
      node[HSVColor::hsv_keys[VALUE]] = f_value;
      return node;
    }

    static bool decode(const Node &node, HSVColor &hsv)
    {
      if (!node.IsMap() || node.size() != 3)
      {
        return false;
      }
      float f_hue = node[HSVColor::hsv_keys[HUE]].as<float>();
      float f_saturation = node[HSVColor::hsv_keys[SATURATION]].as<float>();
      float f_value = node[HSVColor::hsv_keys[VALUE]].as<float>();
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
      if (!node.IsMap() || node.size() != 3)
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
