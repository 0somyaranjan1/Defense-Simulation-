#include "Player.h"

Player::Player(std::string name, int health, double x, double y, double z, std::string team, Database& db) {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::open_array;
    using bsoncxx::builder::stream::close_array;
    using bsoncxx::builder::stream::finalize;

    auto doc = document{} 
        << "name" << name
        << "health" << health
        << "position" << open_document
            << "x" << x
            << "y" << y
            << "z" << z
        << close_document
        << "team" << team
        << "kills" << 0
        << "weapons" << open_array << close_array << finalize;

    bsoncxx::document::value doc_value = doc;

    auto collection = db.getDatabase()["players"];
    collection.insert_one(doc_value.view());
}

mongocxx::cursor Player::getAllPlayers(Database& db) {
    auto collection = db.getDatabase()["players"];
    return collection.find({});
}

void Player::addWeapon(const bsoncxx::document::view& weapon, const bsoncxx::document::view& player, Database& db) {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;

    bsoncxx::oid player_id = player["_id"].get_oid().value;
    
    auto collection = db.getDatabase()["players"];
    auto filter = document{} << "_id" << player_id << finalize;
    auto update = document{} 
        << "$push" << open_document 
            << "weapons" << weapon
        << close_document 
        << finalize;
    
    collection.update_one(filter.view(), update.view());
}

void Player::attack(const bsoncxx::document::view& weapon, const bsoncxx::document::view& player, const bsoncxx::document::view& enemy, Database& db) {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::finalize;

    auto weapons_array = player["weapons"].get_array().value;
    bool has_weapon = false;
    int weapon_index = -1;
    int current_index = 0;
    bsoncxx::oid weapon_id = weapon["_id"].get_oid().value;

    for (const auto& w : weapons_array) {
        if (w.get_document().value["_id"].get_oid().value == weapon_id) {
            has_weapon = true;
            weapon_index = current_index;
            break;
        }
        current_index++;
    }

    if (!has_weapon) {
        std::cout << "Player doesn't have this weapon!" << std::endl;
        return;
    }

    int ammo = weapon["ammo"].get_int32().value;
    int damage = weapon["damage"].get_int32().value;
    int enemy_health = enemy["health"].get_int32().value;
    std::string weapon_name(weapon["name"].get_string().value);
    std::string player_name(player["name"].get_string().value);
    std::string enemy_name(enemy["name"].get_string().value);
    
    
    if (ammo > 0) {
        auto players_coll = db.getDatabase()["players"];
        bsoncxx::oid player_id = player["_id"].get_oid().value;

        // Update ammo in player's weapons array using specific index
        auto player_weapon_filter = document{} << "_id" << player_id << finalize;
        auto player_weapon_update = document{} 
            << "$set" << open_document 
                << "weapons." + std::to_string(weapon_index) + ".ammo" << (ammo - 1)
            << close_document 
            << finalize;
        
        players_coll.update_one(player_weapon_filter.view(), player_weapon_update.view());

        // Update enemy health
        int new_health = enemy_health - damage;
        bsoncxx::oid enemy_id = enemy["_id"].get_oid().value;
        auto enemy_players_coll = db.getDatabase()["players"];
        auto enemy_filter = document{} << "_id" << enemy_id << finalize;
        auto enemy_update = document{} 
            << "$set" << open_document 
                << "health" << new_health
            << close_document 
            << finalize;
        enemy_players_coll.update_one(enemy_filter.view(), enemy_update.view());

        std::cout << player_name << " attacked " << enemy_name << " with " << weapon_name 
                  << "! Enemy health: " << new_health << std::endl;

        // If enemy died, increment player's kills
        if (new_health <= 0) {
            bsoncxx::oid player_id = player["_id"].get_oid().value;
            int kills = player["kills"].get_int32().value;
            auto player_filter = document{} << "_id" << player_id << finalize;
            auto player_update = document{} 
                << "$set" << open_document 
                    << "kills" << (kills + 1)
                << close_document 
                << finalize;
            players_coll.update_one(player_filter.view(), player_update.view());
            
            std::cout << enemy_name << " is eliminated by " << player_name 
                      << "! Total kills: " << (kills + 1) << std::endl;
        }
    } else {
        std::cout << weapon_name << " is out of ammo!" << std::endl;
    }
}




void Player::display(const bsoncxx::document::view& player) {
    std::string name(player["name"].get_string().value);
    int health = player["health"].get_int32().value;
    std::string team(player["team"].get_string().value);
    int kills = player["kills"].get_int32().value;
    
    // Display player info
    std::cout << "Player: " << name 
              << " | Health: " << health 
              << " | Team: " << team 
              << " | Kills: " << kills << std::endl;
    
    // Display position
    auto position = player["position"].get_document().value;
    std::cout << "Position: "
              << "X: " << position["x"].get_double().value
              << " Y: " << position["y"].get_double().value
              << " Z: " << position["z"].get_double().value << std::endl;
    
    // Display weapons
    std::cout << "Weapons:" << std::endl;
    auto weapons = player["weapons"].get_array().value;
    for (const auto& weapon : weapons) {
        auto weapon_doc = weapon.get_document().value;
        std::cout << "- " << std::string(weapon_doc["name"].get_string().value)
                  << " | Damage: " << weapon_doc["damage"].get_int32().value
                  << " | Ammo: " << weapon_doc["ammo"].get_int32().value
                  << " | Range: " << weapon_doc["range"].get_double().value << "m"
                  << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}