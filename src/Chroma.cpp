#include "Chroma.h"

namespace glow
{
  std::string Chroma::keys[Chroma::KEY_COUNT] = {
      "length",
      "source",
      "target",
      "delta",
  };

  // bool Chroma::setup(uint16_t p_length,
  //                    int16_t p_delta,
  //                    Color p_source,
  //                    Color p_target)
  // {
  //   length = p_length;
  //   delta = p_delta;
  //   hsv_source.from_rgb(p_source);
  //   hsv_target.from_rgb(p_target);
  //   return setup();
  // }

  bool Chroma::setup(uint16_t p_length,
                     HSVColor p_source,
                     HSVColor p_target,
                     int16_t p_delta)
  {
    length = p_length;
    delta = p_delta;
    hsv_source = p_source;
    hsv_target = p_target;
    return setup();
  }

  bool Chroma::setup(uint16_t p_length,
                     Color p_source,
                     HSVColor p_target,
                     int16_t p_delta)
  {
    length = p_length;
    delta = p_delta;
    hsv_source.from_rgb(p_source);
    hsv_target = p_target;
    return setup();
  }

  bool Chroma::setup()
  {
    if (length == 0)
    {
      return false;
    }
    rgb_source = hsv_source.to_rgb();
    rgb_target = hsv_target.to_rgb();
    gradient_amount = (255.0 / static_cast<float>(length)) / 255.0;
    return true;
  }

}