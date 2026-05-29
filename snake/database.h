#pragma once
#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& filename);
    ~Database();
    void query(const std::string& sql);
    int getHighScore(const std::string& player);

private:
    sqlite3* db;
};