#include "Weapon.h"

Weapon::Weapon(std::string name, int damage, int ammo, double range){
    (*this).name = name;
    (*this).damage = damage;
    (*this).ammo = ammo;
    (*this).range = range;
};

void Weapon::fire() {
    if((*this).ammo > 0) {
        ammo--;
        std::cout << name << " fired! Ammo left: " << ammo << std::endl;
    } else {
        std::cout<<(*this).name<<" IS OUT OF AMMO"<<std::endl;
    }
}

void Weapon::reload() {
    ammo = 30;
    std::cout << name << " reloaded. Ammo: " << ammo << std::endl;
}

void Weapon::display() {
    std::cout << "Weapon: " << name << " | Damage: " << damage 
              << " | Ammo: " << ammo << " | Range: " << range << "m" << std::endl;
}