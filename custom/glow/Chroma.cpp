#include "Chroma.h"

namespace glow
{
#ifndef MICRO_CONTROLLER
  std::string Chroma::make_code()
  {
    std::stringstream s;
    s << "{" << length << ",";
    // << hsv_source.make_code() << ","
    // << hsv_target.make_code() << ","
    for (auto &color : colors)
    {
      s << color.make_code() << ",";
    }
    s << hue_shift << "}";
    return s.str();
  }

  std::string Chroma::keys[Chroma::KEY_COUNT] = {
      "length",
      "source",
      "target",
      "hue_shift",
      "colors",
  };
  Palette Chroma::palette{};
#endif

  // bool Chroma::setup(uint16_t p_length,
  //                    int16_t p_hue_shift,
  //                    Color p_source,
  //                    Color p_target)
  // {
  //   length = p_length;
  //   hue_shift = p_hue_shift;
  //   hsv_source.from_rgb(p_source);
  //   hsv_target.from_rgb(p_target);
  //   return setup();
  // }

  bool Chroma::setup(uint16_t p_length,
                     HSVColor p_source,
                     HSVColor p_target,
                     int16_t p_hue_shift)
  {
    length = p_length;
    hue_shift = p_hue_shift;
    colors.push_back(p_source);
    colors.push_back(p_target);
    return setup();
  }

  bool Chroma::setup(uint16_t p_length,
                     Color p_source,
                     HSVColor p_target,
                     int16_t p_hue_shift)
  {
    length = p_length;
    hue_shift = p_hue_shift;
    HSVColor source;
    source.from_rgb(p_source);
    colors.push_back(source);
    colors.push_back(p_target);
    return setup();
  }

  bool Chroma::setup()
  {
    if (length == 0)
    {
      return false;
    }

    uint16_t size = colors.size();
    for (; size < 2; size++)
    {
      colors.push_back(color_default);
    }

    quick_color = colors[0].to_rgb();
    // rgb_source = hsv_source.to_rgb();
    // rgb_target = hsv_target.to_rgb();
    // gradient_amount = (static_cast<float>(byte_limit) /
    //                    static_cast<float>(length)) /
    //                   static_cast<float>(byte_limit);
    segment_size = length / size;
    return true;
  }

  bool Chroma::setup(uint16_t p_length,
                     std::initializer_list<HSVColor> p_colors,
                     int16_t p_hue_shift)
  {
    length = p_length;
    colors = p_colors;
    hue_shift = p_hue_shift;
    return setup();
  }

  Color Chroma::map(uint16_t index)
  {
    uint16_t size = colors.size();
    if (size < 2 || index == 0)
    {
      return quick_color;
    }

    // d.quot == segment
    // d.rem == index within segment
    div_t d = div(index, segment_size);
    HSVColor first = colors[d.quot];
    HSVColor last = colors[d.quot + 1];
    return first.to_gradient(last, d.rem, d.quot).to_rgb();
  }

  void Chroma::update()
  {
    if (hue_shift == 0)
      return;

    for (auto &hsv : colors)
    {
      hsv.hue += hue_shift;
      if (hsv.hue > hue_limit)
      {
        hsv.hue = (hue_shift < 0) ? hue_limit : 0;
      }
    }
    quick_color = colors.begin()->to_rgb();
  }
}