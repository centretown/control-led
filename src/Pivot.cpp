#include "Pivot.h"
#include <math.h>

namespace glow
{
    void Pivot::setup_diagonal(uint16_t rows, uint16_t columns)
    {
        first = 0;
        uint16_t lesser = std::min(rows, columns);
        for (uint16_t i = 0; i < lesser; i++)
        {
            first += i;
        }

        offset = lesser - 1;
        last = first +
               (columns - lesser) * rows +
               rows - 1;
    }

    void Pivot::setup_centred(uint16_t rows, uint16_t columns)
    {
    }
}
