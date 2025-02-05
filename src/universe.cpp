
#include <queue>
#include <cstdint>
#include <assert.h>
#include <iostream>
#include <functional>
#include "constants.hpp"
#include "cue.cpp"

class Universe {
    
    Cue<idn,MAX_PLANETS> lop;
    idn lopCount;

    public:
        Universe(){
            std::array<idn,MAX_PLANETS> arr;
            for(idn i = 0; i<MAX_PLANETS; i++){
                arr[i]=i;
            }
            lop = Cue(arr);
            lopCount = 0;
        }

        void deletePlanets(VecCue<idn> rml);
        idn addPlanet();
        void log();
        idn lopPos();
        idn getLopCount();

};



void Universe::deletePlanets(VecCue<idn> rml)
{ // removes elements of rml from lop, then adds them to the back of the queue. Since rml will always be constructed in the order lop is in, no searching is required, and we can do this in linear time.
    lop.bulkPop(rml);
    lopCount -= rml.size();
}

idn Universe::addPlanet()
{ // Increases the number of planets by 1.
    lopCount++;
    return lop[lopCount-1];
}

void Universe::log()
{ // Logs all the id numbers in lop, in order.
    std::cout << "Planet count: " << lopCount << "\n";
    logCue(lop);
}

idn Universe::lopPos()
{ // Returns the position of the queue in lop.
    return lop.position;
}

idn Universe::getLopCount()
{ // Returns the number of planets currently 'alive' in lop.
    return lopCount;
}