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
  struct Chroma
  {
    enum : uint8_t
    {
      LENGTH,
      DELTA,
      SOURCE,
      TARGET,
      KEY_COUNT,
    };

    uint16_t length = 10;
    int16_t delta = 1;
    HSVColor hsv_source;
    HSVColor hsv_target;

    Color rgb_source;
    Color rgb_target;
    float gradient_amount = 1.0;

    bool setup(uint16_t p_length, int16_t p_delta,
               Color p_source, Color p_target);
    bool setup(uint16_t p_length, int16_t p_delta,
               HSVColor p_source, HSVColor p_target);
    bool setup(uint16_t p_length, int16_t p_delta,
               Color p_source, HSVColor p_target);
    bool setup();

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