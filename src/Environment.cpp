#include "Environment.h"

Environment::Environment(std::string weather, std::string terrainType) {
    (*this).weather = weather;
    (*this).terrainType = terrainType;
}

void Environment::changeWeather(std::string newWeather) {
    weather = newWeather;
    std::cout << "Weather changed to: " << weather << std::endl;
}

void Environment::display() {
    std::cout << "Environment: " << terrainType << " | Weather: " << weather << std::endl;
}
