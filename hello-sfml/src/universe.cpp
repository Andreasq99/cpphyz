
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include "./planet.cpp"


typedef std::unique_ptr<Planet* []> plist;
class Universe{
    private:
        plist lop;
        int lopSize;
        const float G = .1f;
        int trackcount = 5;
        int lopmax = 0;
        double lopmean = 0.0;
        int framecount = 0;
        sf::Clock frame_clock;
        sf::Clock global_clock;
        std::unique_ptr<sf::CircleShape*[]> path;
    public:
        void fixLop();
        void restart();
        void addLop(plist newPlanets, int size);
        Planet* getPlanet(int index);

        Universe(){
            lopSize = 1;
            lop = std::make_unique<Planet*[]>(lopSize);
            
        }
};

void Universe::fixLop(){
    plist newLop;
    int i = 0;
    int j = 0;
    while(i+j<lopSize){
        if(lop[i]==nullptr){
            while(i+j<lopSize){
                j++;
                if(i+j<lopSize && lop[i+j]!=nullptr){
                    break;
                }
            }
            if(i+j<lopSize){
                lop[i] = lop[i+j];
                lop[i+j] = nullptr;
            }
        }
        i++;
    }
    newLop = std::make_unique<Planet*[]>(i);
    for(int k=0; k<i;k++){
        newLop[k] = lop[k];
    }
    lop = std::move(newLop);
}

void Universe::restart(){
    lopSize = 1;
    lop = std::move(std::make_unique<Planet*[]>(lopSize));

}

void Universe::addLop(plist newPlanets, int size){
    plist newLop = std::make_unique<Planet*[]>(lopSize+size);
    for(int i=0; i< lopSize; i++){
        newLop[i] = lop[i];
    }
    for(int i=0; i<size;i++){
        newLop[lopSize+i] = newPlanets[i];
    }
    lopSize += size;
    lop = std::move(newLop);
}

Planet* Universe::getPlanet(int index){
    return lop[index];
}

