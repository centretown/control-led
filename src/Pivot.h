#pragma once

#include <stdint.h>
#include <string>
#include <unordered_map>

#include "base.h"
namespace glow
{
    struct Pivot
    {
        uint16_t first{0}; // middle beginning
        uint16_t last{0};  // middle end
        uint16_t offset{0};

        void setup_diagonal(uint16_t rows, uint16_t columns);
        void setup_centred(uint16_t rows, uint16_t columns);
    };
}