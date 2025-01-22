
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <format>
#include <sstream>

std::string statLog(sf::Clock& gc, sf::Time& ftime, int& lopmax, double& lopmean, int& framecount, int& loptot){
    std::stringstream log_str;
    log_str << "Time elapsed: " << gc.getElapsedTime().asSeconds() << "s\n";
    log_str << "Frame rate: " << ftime.asMilliseconds() << " ms/f, " << 1/ftime.asSeconds() <<" fps\n" << "\n";
    log_str << "Number of particles: " << loptot << "\n";
    if(loptot > lopmax){
        lopmax = loptot;
    }
    log_str << "Maximum number of particles: " << lopmax << "\n";
    lopmean = lopmean*(framecount);
    lopmean += loptot;
    lopmean = lopmean/(framecount+1);
    log_str << "Mean number of particles: " << lopmean;
    return log_str.str();
}