#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using sf::Vector2f;

class Planet : public sf::CircleShape {
    public: 
        Vector2f pastpos;
        Vector2f acc;

        Vector2f getPos();
        void step(float dt);
        void pull(Planet* P,float G);
    
        Planet(Vector2f pos, Vector2f vel, int r, sf::Color col){
            setRadius(r);
            setPosition(pos);
            acc = Vector2f(0,0);
            setFillColor(col);
            pastpos = getPosition() - vel;
            // std::cout << "Created a new planet at " << getPos().x << "," << getPos().y <<".\n";
        }

        Planet(Vector2f pos, int r, sf::Color col){
            Planet(pos,Vector2f(2,3),r,col);
        }

        Planet(Vector2f pos, int r){
            sf::Color col(static_cast<uint8_t>(100),static_cast<uint8_t>(0),static_cast<uint8_t>(100));
            Planet(pos,r,col);
        }

        ~Planet(){}
};

Vector2f Planet::getPos(){
    return getPosition() + Vector2f(getRadius(),getRadius());
}



void Planet::step(float dt){
    Vector2f temp = getPosition();
    setPosition(2.f*temp - pastpos + pow(dt/1000,2.f)*(acc));
    // setPosition(2.f*temp - pastpos + acc);
    pastpos = temp;
}

void Planet::pull(Planet* P,float G){
    Vector2f diff = (getPos() - (P->getPos()));
    // std::cout << "previous acceleration: " << acc.length() << "\n";
    // std::cout << "Planet has radius " << P->getRadius() << "and will exert an acceleration of " << (G*pow(P->getRadius(),3.f)/(pow(diff.length(),2.f))) << "\n";
    if(diff.length() !=0){
        acc -= (G*pow(P->getRadius(),3.f)/(pow(diff.length(),3.f)))*diff;
    }
    // std::cout << "current acceleration: " << acc.length() << "\n";
}