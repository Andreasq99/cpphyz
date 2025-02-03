
#include <queue>
#include <cstdint>
#include <assert.h>
#include <iostream>
#include <functional>
#include "constants.hpp"
#include "cue.cpp"

using idn = uint16_t;

class Universe {
    public:
        Universe(){
            std::array<idn,MAX_PLANETS> arr;
            for(idn i = 0; i<MAX_PLANETS; i++){
                arr[i]=i;
            }
            lop = Cue(arr);
            lopCount = 0;
        }

        // template<typename T> T iterateLop(T callback(idn id));
        void deletePlanets(Cue<idn,MAX_PLANETS> rml);
        void addPlanet();
        void log();
        idn loppos();

    private:
        Cue<idn,MAX_PLANETS> lop;
        idn lopCount;
};

// template<typename T> T Universe::iterateLop(T callback(idn id)){ // calls callback() with the front element of lop, then pushes it to the back of the queue if successful. Otherwise, returns false.
//     for(i=0;i<MAX_PLANETS;i++){

//     }
// }

void Universe::deletePlanets(Cue<idn,MAX_PLANETS> rml){ // removes elements of rml from lop, then adds them to the back of the queue.
    idn rid = rml.front();
    for(idn i = 0; i < MAX_PLANETS; i++){
        if(rid != lop.front()){
            lop.next();
        } else {
            rml.pop();
            rid = rml.front();
            lop.pop();
            lopCount--;
            if(rid == MAX_PLANETS){break;}
        }
    }
}

void Universe::addPlanet(){
    lopCount++;
}

// void Universe::log(){ 
//     for(idn i = 0; i < lopCount; i++){
//         std::cout << "Element " << iterateLop() << " found.\n";
//     }
//     for(idn i = 0; i < MAX_PLANETS - lopCount;i++){
//         iterateLop();
//     }
//     std::cout << "\n";
// }

void Universe::log(){
    std::cout << "Planet count: " << lopCount << "\n";
    logCue(lop);
}