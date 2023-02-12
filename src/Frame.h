#pragma once
#include <list>

#ifndef STRIP_YAML
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

  public:
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

#ifndef STRIP_YAML
    enum : uint8_t
    {
      LENGTH,
      INTERVAL,
      LAYERS,
      KEY_COUNT,
    };
    static std::string keys[KEY_COUNT];
    friend YAML::convert<Frame>;
#endif
  };
} // namespace glow

#ifndef STRIP_YAML
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
      // node[Frame::keys[Frame::LAYERS]] = frame.layers;
      Node list;
      for (auto layer : frame.layers)
      {
        list.push_back(layer);
      }
      node[Frame::keys[Frame::LAYERS]] = list;
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

      auto layers = node[Frame::keys[Frame::LAYERS]];
      if (!layers.IsSequence())
      {
        frame.setup();
        return false;
      }

      for (auto i = 0; i < layers.size(); i++)
      {
        frame.push_back(layers[i].as<Layer>());
      }
      frame.setup();
      return true;
    }
  };
}
#endif