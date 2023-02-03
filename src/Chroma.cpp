#include "Chroma.h"

namespace glow
{
  bool Chroma::setup(uint16_t p_length,
                     int16_t p_delta,
                     Color p_source,
                     Color p_target)
  {
    rgb_source = p_source;
    hsv_source.from_rgb(rgb_source);
    rgb_target = p_target;
    hsv_target.from_rgb(rgb_target);
    return setup(p_length, p_delta);
  }

  bool Chroma::setup(uint16_t p_length,
                     int16_t p_delta,
                     HSVColor p_source,
                     HSVColor p_target)
  {
    hsv_source = p_source;
    rgb_source = hsv_source.to_rgb();
    hsv_target = p_target;
    rgb_target = hsv_target.to_rgb();
    return setup(p_length, p_delta);
  }

  bool Chroma::setup(uint16_t p_length,
                     int16_t p_delta,
                     Color p_source,
                     HSVColor p_target)
  {
    rgb_source = p_source;
    hsv_source.from_rgb(rgb_source);
    hsv_target = p_target;
    rgb_target = hsv_target.to_rgb();
    return setup(p_length, p_delta);
  }

  bool Chroma::setup(uint16_t p_length, int16_t p_delta)
  {
    if (p_length == 0)
    {
      return false;
    }
    length = p_length;
    delta = p_delta;
    gradient_amount = (255.0 / static_cast<float>(p_length)) / 255.0;
    return true;
  }

}