#include <cstdint>

#if !defined(CONSTANTS_H)
#define CONSTANTS_H

    using cid = uint8_t;
    using idn = uint16_t;
    constexpr idn MAX_PLANETS = 10;
    constexpr cid COMPONENT_COUNT = 2;
    constexpr cid ACTION_LENGTH = 5;
#endif