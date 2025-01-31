
#include <queue>
#include <cstdint>
#include <assert.h>
#include <iostream>

using idn = uint16_t;
idn MAX_PLANETS = 10;
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

        bool iterateLop(bool callback(idn id));
        void deletePlanets(std::queue<idn> rml);
        void addPlanet();
        void log();

    private:
        std::queue<idn> lop{};
        idn lopCount;
};

bool Universe::iterateLop(bool callback(idn id)){ // calls callback() with the front element of lop, then pushes it to the back of the queue if successful. Otherwise, returns false.
    idn id = lop.front();
    if(callback(id)){
        lop.pop();
        lop.push(id);
        return true;
    }
    return false;
}

void Universe::deletePlanets(std::queue<idn> rml){ // removes elements of rml from lop, then adds them to the back of the queue.
    idn rid = rml.front();
    for(idn i = 0; i < MAX_PLANETS; i++){
        idn id = lop.front();
        lop.pop();
        if(rid != id){
            lop.push(id);
        } else {
            rml.pop();
            rml.push(rid);
            rid = rml.front();
            lopCount--;
            // std::cout << "moved to id " << rid << "\n";
        }
    }
    // std::cout << "rml has size "<<rml.size()<<"\n";
    int rmlct = rml.size();
    for(int i = 0; i < rmlct; i++){
        // std::cout << "Adding element " << rml.front() << " to lop.\n";
        lop.push(rml.front());
        rml.pop();
    }
    // std::cout << "\n";
}

void Universe::addPlanet(){

}

void Universe::log(){ 
    for(idn i = 0; i < MAX_PLANETS; i++){
        iterateLop([](idn id) {
            std::cout << "Element " << id << " found.\n";
            return true;
        });
    }
    std::cout << "\n";
}