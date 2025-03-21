#include "Vehicle.h"

Vehicle::Vehicle(std::string name, double speed, double x, double y, double z, std::string type) {
    (*this).name = name;
    (*this).speed = speed;
    (*this).type = type;
    (*this).position.x = x;
    (*this).position.y = y;
    (*this).position.z = z;
}

void Vehicle::move(double newX, double newY, double newZ) {
    position.x = newX;
    position.y = newY;
    position.z = newZ;
    std::cout << name << " moved to (" << newX << ", " << newY << ", " << newZ << ")" << std::endl;
}

void Vehicle::display() {
    std::cout << "Vehicle: " << name << " | Type: " << type << " | Speed: " << speed << " km/h" << std::endl;
}