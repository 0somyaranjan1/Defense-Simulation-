#include "Weapon.h"

Weapon::Weapon(std::string name, int damage, int ammo, double range, Database& db) {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    auto doc = document{}
        << "name" << name
        << "damage" << damage
        << "ammo" << ammo
        << "range" << range
        << finalize;

    auto collection = db.getDatabase()["weapons"];
    collection.insert_one(doc.view());
}

mongocxx::cursor Weapon::getAllWeapons(Database& db) {
    auto collection = db.getDatabase()["weapons"];
    return collection.find({});
}

void Weapon::fire(const bsoncxx::document::view& weapon, Database& db) {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;

    int ammo = weapon["ammo"].get_int32().value;
    std::string name(weapon["name"].get_string().value);
    bsoncxx::oid weapon_id = weapon["_id"].get_oid().value;
    
    if (ammo > 0) {
        // Update database
        auto collection = db.getDatabase()["weapons"];
        auto filter = document{} << "_id" << weapon_id << finalize;
        auto update = document{}
            << "$set" << open_document
                << "ammo" << (ammo - 1)
            << close_document
            << finalize;
        
        collection.update_one(filter.view(), update.view());
        std::cout << name << " fired! Ammo left: " << (ammo - 1) << std::endl;
    } else {
        std::cout << name << " IS OUT OF AMMO" << std::endl;
    }
}

void Weapon::reload(const bsoncxx::document::view& weapon, Database& db) {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;

    std::string name(weapon["name"].get_string().value);
    bsoncxx::oid weapon_id = weapon["_id"].get_oid().value;

    // Update database
    auto collection = db.getDatabase()["weapons"];
    auto filter = document{} << "_id" << weapon_id << finalize;
    auto update = document{}
        << "$set" << open_document
            << "ammo" << 30
        << close_document
        << finalize;
    
    collection.update_one(filter.view(), update.view());
    std::cout << name << " reloaded. Ammo: 30" << std::endl;
}

void Weapon::display(const bsoncxx::document::view& weapon) {
    std::cout << "Weapon: " << std::string(weapon["name"].get_string().value)
              << " | Damage: " << weapon["damage"].get_int32().value
              << " | Ammo: " << weapon["ammo"].get_int32().value
              << " | Range: " << weapon["range"].get_double().value << "m" << std::endl;
}