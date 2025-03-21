#include "Player.h"

Player::Player(std::string name, int health, double x, double y, double z, std::string team) {
    (*this).name = name;
    (*this).health = health;
    (*this).team = team;
    (*this).kills = 0;
    (*this).position.x = x;
    (*this).position.y = y;
    (*this).position.z = z;
}

void Player::addWeapon(Weapon weapon) {
    weapons.push_back(weapon);
}

void Player::attack(Player &enemy, Weapon &weapon) {
    if (weapon.ammo > 0) {
        weapon.fire();
        enemy.health -= weapon.damage;

        std::cout << name << " attacked " << enemy.name << " with " << weapon.name 
                  << "! Enemy health: " << enemy.health << std::endl;

        if (enemy.health <= 0) {
            kills++;
            std::cout << enemy.name << " is eliminated by " << name << "! Total kills: " << kills << std::endl;
        }
    } else {
        std::cout << weapon.name << " has no ammo!" << std::endl;
    }
}

void Player::display() {
    std::cout << "Player: " << name << " | Health: " << health 
              << " | Team: " << team << " | Kills: " << kills << std::endl;
    std::cout << "Weapons:" << std::endl;

    for (int i = 0; i < weapons.size(); i++) {  
        weapons[i].display();
    }
}