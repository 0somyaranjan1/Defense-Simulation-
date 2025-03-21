#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>

class Weapon {
public:
    std::string name;
    int damage;
    int ammo;
    double range;

    Weapon(std::string name, int damage, int ammo, double range);
    void fire();
    void reload();
    void display();

};

#endif