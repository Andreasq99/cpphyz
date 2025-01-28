#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include "planet.cpp"
#include "stats.cpp"
#include "sort.cpp"


using std::vector;
using sf::Vector2f;
using namespace std::chrono;



const float G = .1f;
int trackcount = 5;
vector<Planet*> lop;
int lopmax = 0;
double lopmean = 0.0;
int framecount = 0;
sf::Clock frame_clock;
sf::Clock global_clock;
vector<sf::CircleShape*> path;


void addPath(vector<sf::CircleShape*>& tab, Planet* P){
    sf::CircleShape* c = new sf::CircleShape(1.f);
    c->setFillColor(P->getFillColor());
    c->setPosition(P->getGeometricCenter()-sf::Vector2f(1,1));
    tab.push_back(c);
}

void trackerUpdate(){
    if(lop.size()>trackcount){
        for(int i=0;i<trackcount;i++){
            addPath(path,lop[i]);
        }
    }
    if(path.size()>trackcount*1000){
        for(int i=0;i<path.size()-(trackcount*1000);i++){
            delete path[0];
        }
    }
}

Planet* rollPlanet(){
    Vector2f pos = Vector2f(rand()%1720 + 100, rand()%880 + 100);
    int radius = rand()%20 + 1;
    sf::Color color = sf::Color(rand()%256,(2*rand())%256,(3*rand())%256);
    Planet* P = new Planet(pos, Vector2f(0,0),radius,color);
    return P;
}

void garbageCollect(vector<int> rml){
    for(int i:rml){
        delete lop[i];
        lop[i] = nullptr;
    }
}

void addPlanet(Planet* P){
    lop.push_back(P);
}

void update(int& dt, sf::Vector2u dims){
    for(Planet* r : lop){
        for(Planet* s : lop){
            if(r != s){
                r->pull(s,G);
            }
        }
    }
    vector<int> rml;
    int ind = 0;
    for(Planet* r : lop){
        r->step(dt);
        Vector2f p = r->getPos();
        if(p.x> 2420 || p.x < -500 || p.y < -500 || p.y > 1580 || p.x != p.x || p.y != p.y){
            rml.push_back(ind);
        }
        ind++;
    }
    sort(rml);
    trackerUpdate();
    garbageCollect(rml);
}

void restart(){
    lop.erase(lop.begin(),lop.end());
    lopmax = 0;
    lopmean = 0;
    framecount = 0;
    global_clock.restart();
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    global_clock.restart();
    sf::Font font("./Assets/calibri.ttf");
    sf::Text text(font,"",14U);
    sf::Vector2u dims = window.getSize();
    
    srand(std::time(nullptr));
    
    // addPlanet(new Planet(Vector2f(200,500),Vector2f(0,0),20,sf::Color(255,0,0)));
    // addPlanet(new Planet(Vector2f(1500,600),Vector2f(0,0),10,sf::Color(0,255,0)));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if  (event->is<sf::Event::Closed>()||
                (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)){
                    window.close();
            }
            if(event->is<sf::Event::KeyPressed>()){
                if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter){
                    restart();
                }
            }
        }

        window.clear();

        int loptot = lop.size();
        sf::Time frame_time = frame_clock.restart();
        int frame_latency = frame_time.asMilliseconds();

        if(rand()%5==1){
            milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            srand(ms.count());
            Planet* P = rollPlanet();
            addPlanet(P);
        }

        update(frame_latency,dims);

        text.setString(statLog(global_clock, frame_time,lopmax,lopmean,framecount,loptot));
        // std::cout << "About to draw!\n";

        // draw(window,text);
        for(Planet* P : lop){
            window.draw(*P);
            // std::cout << "Drew a planet at coordinates " << P->getPos().x << "," << P->getPos().y << ".\n";
        }
        for(sf::CircleShape* c: path){
            window.draw(*c);
        }
        // std::cout << "Screen Drawn.\n";
        window.draw(text);

        window.display();
        // std::cout << "Displayed frame!\n";

        framecount++;
    }
}
