#pragma once

#include <stdint.h>
#include <string>
#include <yaml-cpp/yaml.h>

#include "esphome/core/color.h"
#include "esphome/components/light/esp_hsv_color.h"
using esphome::Color;
using esphome::light::ESPHSVColor;

#include "base.h"
#include "HSVColor.h"

namespace glow
{
  const HSVColor source_default = {0, 255, 255};
  const HSVColor target_default = {hue_limit, 0, 255};
  const Color rgb_source_default = {255, 0, 0};
  const Color rgb_target_default = {255, 255, 255};

  class Chroma
  {
  public:
    enum : uint8_t
    {
      LENGTH,
      SOURCE,
      TARGET,
      DELTA,
      KEY_COUNT,
    };

  private:
    uint16_t length = 0;
    HSVColor hsv_source = source_default;
    HSVColor hsv_target = target_default;
    int16_t delta = 0;

    Color rgb_source = rgb_source_default;
    Color rgb_target = rgb_target_default;
    float gradient_amount = 0.0;
    friend YAML::convert<Chroma>;

  public:
    // bool setup(uint16_t p_length, int16_t p_delta,
    //            Color p_source, Color p_target);

    bool setup(uint16_t p_length,
               HSVColor p_source = source_default,
               HSVColor p_target = target_default,
               int16_t p_delta = 0);

    bool setup(uint16_t p_length,
               Color p_source,
               HSVColor p_target = target_default,
               int16_t p_delta = 0);

    bool setup();

    uint16_t get_length() const ALWAYS_INLINE { return length; }
    int16_t get_delta() const ALWAYS_INLINE { return delta; }
    HSVColor get_hsv_source() const ALWAYS_INLINE { return hsv_source; }
    HSVColor get_hsv_target() const ALWAYS_INLINE { return hsv_target; }
    Color get_rgb_source() const ALWAYS_INLINE { return rgb_source; }
    Color get_rgb_target() const ALWAYS_INLINE { return rgb_target; }
    float get_gradient_amount() const ALWAYS_INLINE { return gradient_amount; }

    // bool set_length(uint16_t a_length) ALWAYS_INLINE
    // {
    //   length = a_length;
    //   return setup();
    // }
    // void set_delta(int16_t a_delta) ALWAYS_INLINE
    // {
    //   delta = a_delta;
    //   setup();
    // }
    // void set_hsv_source(HSVColor a_source) ALWAYS_INLINE
    // {
    //   hsv_source = a_source;
    //   setup();
    // }
    // void set_hsv_target(HSVColor a_target) ALWAYS_INLINE
    // {
    //   hsv_target = a_target;
    //   setup();
    // }
    // void set_rgb_source(Color a_source) ALWAYS_INLINE
    // {
    //   rgb_source = a_source;
    //   setup();
    // }
    // void set_rgb_target(Color a_target) ALWAYS_INLINE
    // {
    //   rgb_target = a_target;
    //   setup();
    // }

    Color map(uint16_t index)
    {
      return step_gradient(static_cast<float>(index) * gradient_amount);
    }

    void update_hue() ALWAYS_INLINE
    {
      if (delta == 0)
        return;
      hsv_source.hue += delta;
      rgb_source = hsv_source.to_rgb();
      hsv_target.hue += delta;
      rgb_target = hsv_target.to_rgb();
    }

    Color step_gradient(float shift_amount) ALWAYS_INLINE
    {
      return Color(red_shift(shift_amount),
                   green_shift(shift_amount),
                   blue_shift(shift_amount));
    }

  private:
    uint8_t red_shift(float shift_amount) ALWAYS_INLINE
    {
      shift_amount *= static_cast<float>(rgb_target.red - rgb_source.red);
      return rgb_source.red + static_cast<uint8_t>(shift_amount);
    }
    uint8_t green_shift(float shift_amount) ALWAYS_INLINE
    {
      shift_amount *= static_cast<float>(rgb_target.green - rgb_source.green);
      return rgb_source.green + static_cast<uint8_t>(shift_amount);
    }
    uint8_t blue_shift(float shift_amount) ALWAYS_INLINE
    {
      shift_amount *= static_cast<float>(rgb_target.blue - rgb_source.blue);
      return rgb_source.blue + static_cast<uint8_t>(shift_amount);
    }

  public:
    static std::string keys[KEY_COUNT];
  };
}

namespace YAML
{
  using glow::Chroma;

  template <>
  struct convert<Chroma>
  {
    static Node encode(const Chroma &chroma)
    {
      Node node;
      node[Chroma::keys[Chroma::LENGTH]] = chroma.length;
      node[Chroma::keys[Chroma::DELTA]] = chroma.delta;
      node[Chroma::keys[Chroma::SOURCE]] = chroma.hsv_source;
      node[Chroma::keys[Chroma::TARGET]] = chroma.hsv_target;
      return node;
    }

    static bool decode(const Node &node, Chroma &chroma)
    {
      if (!node.IsMap())
      {
        chroma.setup();
        return false;
      }

      for (auto key = 0; key < Chroma::KEY_COUNT; ++key)
      {
        Node item = node[Chroma::keys[key]];
        if (!item.IsDefined())
        {
          continue;
        }

        switch (key)
        {
        case Chroma::LENGTH:
          chroma.length = item.as<uint16_t>();
          break;
        case Chroma::DELTA:
          chroma.delta = item.as<int16_t>();
          break;
        case Chroma::SOURCE:
          chroma.hsv_source = item.as<HSVColor>();
          break;
        case Chroma::TARGET:
          chroma.hsv_target = item.as<HSVColor>();
          break;
        }
      }
      return chroma.setup();
    }
  };
}