#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "Weapon.h"
#include "Database.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/oid.hpp>
#include <mongocxx/cursor.hpp>

class Player {
public:
    Player(std::string name, int health, double x, double y, double z, std::string team, Database& db);

    mongocxx::cursor getAllPlayers(Database& db);

    void addWeapon(const bsoncxx::document::view& weapon, const bsoncxx::document::view& player, Database& db); 

    void attack(const bsoncxx::document::view& weapon, const bsoncxx::document::view& player, const bsoncxx::document::view& enemy, Database& db);

    void display(const bsoncxx::document::view& player);
};

#endif