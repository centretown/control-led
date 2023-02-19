// CAUTION GENERATED FILE
#pragma once
#include "Frame.h"
namespace glow {
enum LIBRARY_INDEX : uint8_t {
FRAME,
SALMON_STRAWBERRY,
FRAME_COUNT,
};
extern Frame library[FRAME_COUNT];
extern Frame &from_library(LIBRARY_INDEX index);
} // namespace glow
