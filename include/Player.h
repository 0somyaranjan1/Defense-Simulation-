#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "Weapon.h"

class Player {
public:
    std::string name;
    int health;
    struct Position { double x, y, z; } position;
    std::string team;
    std::vector<Weapon> weapons;
    int kills;

    Player(std::string name, int health, double x, double y, double z, std::string team);
    void addWeapon(Weapon weapon);
    void attack(Player &enemy, Weapon &weapon);
    void display();
};

#endif