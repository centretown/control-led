// CAUTION GENERATED FILE
#pragma once
#include "Frame.h"
namespace glow {
enum LIBRARY_INDEX : uint8_t {
FRAME,
SALMON_STRAWBERRY,
FRAME_COUNT,
};
extern const char *library_names[FRAME_COUNT];extern Frame library[FRAME_COUNT];
extern Frame &from_library(LIBRARY_INDEX index);
extern const char *library_name(LIBRARY_INDEX index);
} // namespace glow
