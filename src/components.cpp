
#include <cstdint>
#include <assert.h>
#include "constants.hpp"
#include "cue.cpp"

struct PhysicsComponent{
    float x;
    float y;
    float vx;
    float vy;
    int m;

    PhysicsComponent(){
        x = 0;
        y = 0;
        vx = 0;
        vy = 0;
        m = 0;
    }
};


struct GraphicsComponent{
    cid rad;
    cid r;
    cid g;
    cid b;

    GraphicsComponent(){
        rad = 0;
        r = 0;
        g = 0;
        b = 0;
    }
};

template <typename T>
class ComponentArray {
    
    std::array<T,MAX_PLANETS> mComponentArray;

    public: 

        ComponentArray(){
            T a();
            mComponentArray.fill(a);
        }

        void setData(idn id, T component){
            assert(id < MAX_PLANETS && "Index out of bounds.\n");
            mComponentArray[id] = T;
        }

        T getData(idn id){
            assert(id < MAX_PLANETS && "Index out of bounds.\n")
            return mComponentArray[id];
        }

        std::vector<T> liveData(Cue<idn,MAX_PLANETS> cue, idn count){
            idn j = 0;
            std::vector<T> res;
            while(j < count){
                res.push_back(mComponentArray[cue[j]]);
                j++;
            }
            return res;
        }

};
