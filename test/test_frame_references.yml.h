#pragma once

#include <string>

std::string frame_data = R"RAW(length: 20
interval: 48
layers: 
  - &1 length: 20
    begin: 5
    end: 15
    grid:
      length: 20
      rows: 4
      origin: 0
      orientation: 2
    chroma:
      length: 20
      hue_shift: -1
      source:
        hue: 0
        saturation: 100
        value: 100
      target:
        hue: 0
        saturation: 50
        value: 50
  - *1
  - *1
  - *1
  - *1)RAW";
