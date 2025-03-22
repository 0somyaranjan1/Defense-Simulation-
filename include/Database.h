#ifndef DATABASE_H
#define DATABASE_H

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

class Database {
public:
    Database();
    mongocxx::database getDatabase();
private:
    mongocxx::instance instance;
    mongocxx::client client;
    mongocxx::database database;
};

#endif