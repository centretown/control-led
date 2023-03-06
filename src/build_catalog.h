#pragma once
#ifndef MICRO_CONTROLLER

#include "Frame.h"

namespace glow
{
  // extern std::map<std::string, Frame> catalog_items;

  void add_frame_to_catalog(std::string name, Frame &frame);

  bool make_catalog_code();
  bool make_catalog_effects(std::string name, uint16_t rows, uint32_t interval);

} // namespace glow
#endif // MICRO_CONTROLLER
