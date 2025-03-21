#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <string>

class Environment {
public:
    std::string weather;
    std::string terrainType;

    Environment(std::string weather, std::string terrainType);
    void changeWeather(std::string newWeather);
    void display();
};

#endif