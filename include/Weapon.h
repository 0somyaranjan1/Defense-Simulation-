#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/oid.hpp>
#include "Database.h"
#include <mongocxx/cursor.hpp>

class Weapon {
public:
    // Constructor that creates a weapon in database
    Weapon(std::string name, int damage, int ammo, double range, Database& db);
    
    // Get all weapons from database
    mongocxx::cursor getAllWeapons(Database& db);
    
    // Functions that work with database documents
    void fire(const bsoncxx::document::view& weapon, Database& db);
    void reload(const bsoncxx::document::view& weapon, Database& db);
    void display(const bsoncxx::document::view& weapon);
};

#endif