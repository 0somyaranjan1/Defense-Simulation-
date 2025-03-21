#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {
public:
    std::string name;
    double speed;
    struct Position { double x, y, z; } position;
    std::string type;

    Vehicle(std::string name, double speed, double x, double y, double z, std::string type);
    void move(double newX, double newY, double newZ);
    void display();
};

#endif