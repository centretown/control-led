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
    uint16_t rows = 0;
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

      for (auto &layer : layers)
      {
        layer.setup_length(length, rows);
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
      ROWS,
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
  using namespace glow;

  template <>
  struct convert<Frame>
  {
    static void lookup(Node item, Layer &layer)
    {
      if (item.IsMap())
      {
        layer = item.as<Layer>();
        return;
      }

      std::string name = item.as<std::string>();
      if (load_yaml(custom_layer(name), layer))
      {
        return;
      }
      return;
    }

    static Node encode(const Frame &frame)
    {
      Node node;
      node[Frame::keys[Frame::LENGTH]] = frame.length;
      node[Layer::keys[Frame::ROWS]] = frame.rows;
      node[Frame::keys[Frame::INTERVAL]] = frame.interval;
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
      frame.rows =
          node[Frame::keys[Frame::ROWS]].as<uint16_t>();
      frame.interval =
          node[Frame::keys[Frame::INTERVAL]].as<uint32_t>();

      auto layer_nodes = node[Frame::keys[Frame::LAYERS]];
      if (!layer_nodes.IsSequence())
      {
        frame.setup();
        return false;
      }

      Layer layer;
      for (auto node : layer_nodes)
      {
        lookup(node, layer);
        frame.push_back(layer);
      }
      frame.setup();
      return true;
    }
  };
}
#endif