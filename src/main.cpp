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

    VecCue <idn> rml;
    rml.push((idn) 2);
    rml.push((idn) 5);
    rml.push((idn) 9);

    std::cout << "\n";
    for(int i=0;i<rml.size();i++){
        std::cout << rml.position << "\n" << rml.front() << "\n" << rml[0] << "\n";
        rml.pop();
    }
    // std::vector<idn> rmlarr;
    // rmlarr[0]=2;
    // rmlarr[1]=5;
    // for(int i=2;i<MAX_PLANETS; i++){
    //     rmlarr[i]=MAX_PLANETS;
    // }
    // VecCue <uint16_t,0> rml(rmlarr);
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