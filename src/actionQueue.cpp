#include <vector>
#include <functional>

class Action {
    public:
        virtual void execute() = 0;
};

template <typename ArgType>
class ArgAction : public Action {

    std::function<void(ArgType)> func;
    ArgType arg;

public:
    
    ArgAction(std::function<void(ArgType)> func, ArgType arg) 
        : func(func), arg(arg) {};
    
    void execute() override {
        func();
    }
};