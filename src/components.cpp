
#include <cstdint>
#include <assert.h>
#include "constants.hpp"

using cid = uint8_t;
using idn = uint16_t;

struct Frame{
    float x;
    float y;
    float vx;
    float vy;
    int m;
};


struct Graphics{
    uint8_t rad;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// struct Tail{
    
// }

template <typename T>
class ComponentArray {
    public: 
        void insertData(idn id, T component){
            assert(id < MAX_PLANETS && "Index out of bounds.");
            mComponentArray[id] = T;
        }
    private:
        std::array<T,MAX_PLANETS> mComponentArray;
};

class ComponentManager{
    public:

};