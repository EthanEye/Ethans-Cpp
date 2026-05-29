#include "database.h"
#include <iostream>

// constructor - opens the database
Database::Database(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Database opened successfully" << std::endl;
    }
}

// destructor - closes the database
Database::~Database() {
    sqlite3_close(db);
}

// run a query
void Database::query(const std::string& sql) {
    char* errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Query error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Query executed successfully" << std::endl;
    }
}

int Database::getHighScore(const std::string& player) {
    std::string sql = "SELECT high_score FROM leaderboard WHERE player = '" + player + "';";
    int highScore = 0;

    sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
        if (argv[0]) {
            *static_cast<int*>(data) = std::stoi(argv[0]);
        }
        return 0;
    }, &highScore, nullptr);

    return highScore;
}

