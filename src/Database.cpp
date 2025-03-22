#include "Database.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

Database::Database() {
    try {
        mongocxx::uri uri("mongodb://localhost:27017");
        client = mongocxx::client(uri);
        database = client["simulation_db"];
        std::cout << "Connected to MongoDB!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "MongoDB Connection Failed: " << e.what() << std::endl;
    }
}

mongocxx::database Database::getDatabase() {
    return database;
}