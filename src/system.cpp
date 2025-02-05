#include "universe.cpp"
#include "components.cpp"
#include "constants.hpp"
#include <unordered_set>


class System {

    std::unordered_set<idn> entities;
    Universe* universe;
    ComponentArray<PhysicsComponent>* phyz;
    ComponentArray<GraphicsComponent>* graph;
    std::array<void(*)(),ACTION_LENGTH> actionQueue;

    public:
        System()
        {
            universe = &Universe();
            phyz = &ComponentArray<PhysicsComponent>();
            graph = &ComponentArray<GraphicsComponent>();
            actionQueue = std::array<void(*)(),ACTION_LENGTH>();
        }

        void addFunction(int ind, void (*func)());
        void executeActions();

};

class GravSystem : public System {
    public:
        GravSystem()
        {
            
        }
};

void System::addFunction(int ind, void (*func)())
{ // Adds a function to the action queue.
    actionQueue[ind] = func;
}

void System::executeActions()
{ // Runs the actions in the queue.
    for(auto &func : actionQueue){
        func();
    }
}

