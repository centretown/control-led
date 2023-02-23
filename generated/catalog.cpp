// CAUTION GENERATED FILE
#include "catalog.h"
namespace glow
{
  const char *catalog_names[FRAME_COUNT] = {
      "frame",
      "salmon-strawberry",
  };
  Frame catalog[FRAME_COUNT] = {
      {20, 4, 48, //
       {
           {20, 0, 0, 0, {20, 4, 0, 1}, {20, {790, 91, 232}, {1487, 0, 255}, -1}, 0},
           {20, 0, 0, 0, {20, 4, 0, 1}, {20, {1402, 204, 255}, {1402, 204, 255}, 0}, 1},
       }},
      {540, 9, 16, //
       {
           {540, 9, 0, 0, {540, 9, 0, 1}, {540, {807, 124, 234}, {807, 124, 234}, 0}, 0},
           {540, 9, 0, 0, {540, 9, 0, 1}, {540, {1487, 109, 255}, {1487, 109, 255}, 0}, 5},
           {540, 9, 0, 0, {540, 9, 2, 1}, {540, {93, 124, 198}, {93, 124, 198}, 1}, 5},
       }},
  };
  Frame &from_catalog(LIBRARY_INDEX index) { return catalog[index % FRAME_COUNT]; }
  const char *catalog_name(LIBRARY_INDEX index) { return catalog_names[index % FRAME_COUNT]; }
} // namespace glow
