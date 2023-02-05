#pragma once
#include <list>
#include <yaml-cpp/yaml.h>

#include "base.h"
#include "Layer.h"

namespace glow
{
  struct Frame
  {
    enum : uint8_t
    {
      LENGTH,
      INTERVAL,
      LAYERS,
      KEY_COUNT,
    };

    uint16_t length;
    uint32_t interval;
    std::list<Layer> layers;
    bool setup()
    {
      return true;
    }

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
