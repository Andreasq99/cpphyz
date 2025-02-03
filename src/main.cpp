// #include <SFML/Graphics.hpp>
// #include <SFML/Graphics/Shape.hpp>
// #include <SFML/System/Clock.hpp>
// #include <SFML/System/Time.hpp>
// #include <SFML/Graphics/Font.hpp>
// #include <SFML/Graphics/Text.hpp>
#include <array>
#include "universe.cpp"

int main(){
    Universe uni = Universe();
    for(int i=0;i<7;i++){uni.addPlanet();}
    uni.log();

    std::array<uint16_t,MAX_PLANETS> rmlarr;
    rmlarr.fill(MAX_PLANETS);
    rmlarr[0]=2;
    rmlarr[1]=5;
    for(int i=2;i<MAX_PLANETS; i++){
        rmlarr[i]=-1;
    }
    Cue <uint16_t,MAX_PLANETS> rml(rmlarr);
    uni.deletePlanets(rml);
    uni.log();
    uni.addPlanet();
    uni.log();
    // auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    // window.setFramerateLimit(60);
    // sf::Font font("./Assets/calibri.ttf");
    // sf::Text text(font,"",14U);
    // sf::Vector2u dims = window.getSize();
    
    // srand(std::time(nullptr));
    

    return 0;
}