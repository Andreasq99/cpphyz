#include "universe.cpp"

int main(){
    Universe uni = Universe();
    uni.log();
    std::queue<uint16_t> rml;
    rml.push(0);
    rml.push(6);
    uni.deletePlanets(rml);
    uni.log();

    return 0;
}