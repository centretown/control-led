#pragma once
#include <list>

#ifndef USE_ESPHOME
#include <yaml-cpp/yaml.h>
#endif

#include "base.h"
#include "Layer.h"

namespace glow
{
  class Frame
  {
  private:
    uint16_t length = 0;
    uint32_t interval = 16;
    std::list<Layer> layers;

  public:
    bool setup()
    {
      if (length == 0)
      {
        return false;
      }
      return true;
    }

    bool setup(uint16_t p_length, uint32_t p_interval)
    {
      length = p_length;
      interval = p_interval;
      return setup();
    }

    uint16_t get_length() const ALWAYS_INLINE { return length; }
    uint32_t get_interval() const ALWAYS_INLINE { return interval; }

    size_t get_size() const ALWAYS_INLINE { return layers.size(); }
    std::list<Layer>::const_iterator begin() const ALWAYS_INLINE { return layers.begin(); }
    std::list<Layer>::const_iterator end() const ALWAYS_INLINE { return layers.end(); }
    void push_back(Layer layer) ALWAYS_INLINE { layers.push_back(layer); }

    enum : uint8_t
    {
      LENGTH,
      INTERVAL,
      LAYERS,
      KEY_COUNT,
    };
    static std::string keys[KEY_COUNT];
#ifndef USE_ESPHOME
    friend YAML::convert<Frame>;
#endif
  };
} // namespace glow
#ifndef USE_ESPHOME

namespace YAML
{
  using glow::Frame;
  using glow::Layer;

  template <>
  struct convert<Frame>
  {
    static Node encode(const Frame &frame)
    {
      Node node;
      node[Frame::keys[Frame::LENGTH]] = frame.length;
      node[Frame::keys[Frame::INTERVAL]] = frame.interval;
      Node list = node[Frame::keys[Frame::LAYERS]];
      for (auto item : frame.layers)
      {
        list.push_back(item);
      }
      return node;
    }

    static bool decode(const Node &node, Frame &frame)
    {
      if (!node.IsMap())
      {
        frame.setup();
        return false;
      }

      frame.length =
          node[Frame::keys[Frame::LENGTH]].as<uint16_t>();
      frame.interval =
          node[Frame::keys[Frame::INTERVAL]].as<uint32_t>();

      Node layers = node[Frame::keys[Frame::LAYERS]];
      for (auto item : layers)
      {
        frame.push_back(item.as<Layer>());
      }

      return frame.setup();
    }
  };
}
#endif