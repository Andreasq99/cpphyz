
#include <cstdint>

using cid = uint8_t;
using qt = uint16_t;

struct Coords{
    float x;
    float y;
};

struct Physics{
    signed long int m;
    float vx;
    float vy;
};

struct Graphics{
    int rad;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
