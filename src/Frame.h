#pragma once
#include <list>
#include <yaml-cpp/yaml.h>

#include "base.h"
#include "Layer.h"

namespace glow
{
  class Frame
  {
  public:
    enum : uint8_t
    {
      LENGTH,
      INTERVAL,
      LAYERS,
      KEY_COUNT,
    };

  private:
    uint16_t length = 0;
    uint32_t interval = 16;
    std::list<Layer> layers;
    friend YAML::convert<Frame>;

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

    static std::string keys[KEY_COUNT];
    void push_back(Layer layer) ALWAYS_INLINE { layers.push_back(layer); }
  };
} // namespace glow

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
      for (auto iter = frame.layers.begin();
           iter != frame.layers.end(); ++iter)
      {
        list.push_back(*iter);
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
      for (auto iter = layers.begin(); iter != layers.end(); ++iter)
      {
        Node layer = *iter;
        frame.push_back(layer.as<Layer>());
      }

      return frame.setup();
    }
  };
}
