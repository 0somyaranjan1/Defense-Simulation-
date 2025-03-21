#include <iostream>
#include "Player.h"
#include "Vehicle.h"
#include "Environment.h"
#include "Weapon.h"

int main() {
    std::cout << "Simulation Game Starting..." << std::endl;

    Player p1("Sol", 100, 0, 0, 0, "TeamA");
    Weapon rifle("Rifle", 30, 30, 100.0);
    Weapon pistol("Pistol", 15, 12, 50.0);
    p1.addWeapon(rifle);
    p1.addWeapon(pistol);
    p1.display();

    Vehicle v1("Fighter Jet", 900, 50, 200, 0, "Plane");
    v1.display();
    v1.move(100, 300, 50);

    Environment env("Sunny", "City");
    env.display();
    env.changeWeather("Rainy");

    return 0;
}