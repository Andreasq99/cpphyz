
#include <queue>
#include <cstdint>
#include <assert.h>

using idn = uint16_t;
idn MAX_PLANETS = 5000;
using cid = uint8_t;
cid COMPONENT_COUNT = 3;

class Universe {
    public:
        Universe(){
            for(idn i = 0; i<MAX_PLANETS; i++){
                lop.push(i);
            }
            lopCount = 0;
        }

        bool iterateLop(bool callback(idn id)){ //calls callback() with the front element of lop, then pushes it to the back of the queue if successful. Otherwise, returns false.
            idn id = lop.front();
            if(callback(id)){
                lop.pop();
                lop.push(id);
                return true;
            }
            return false;
        }

        void deletePlanets(std::queue<idn> rml){
            assert(id < MAX_PLANETS && "Planet out of queue range");
            
        };

        void addPlanet();

    private:
        std::queue<idn> lop{};
        idn lopCount;
};