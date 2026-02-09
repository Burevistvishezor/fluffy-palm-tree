
cmake_minimum_required(VERSION 3.10)
project(CoreBankingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

add_executable(bank_app
    main.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/Transaction.cpp
    src/Bank.cpp
    src/DatabaseManager.cpp
)

target_link_libraries(bank_app ${SQLite3_LIBRARIES})
include/DatabaseManager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <sqlite3.h>
#include "Account.h"

class DatabaseManager {
    sqlite3* db;

public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    void createTables();
    void saveAccount(const Account& account);
};

#endif
src/DatabaseManager.cpp
#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbName) : db(nullptr) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open database\n";
        db = nullptr;
    }
}

DatabaseManager::~DatabaseManager() {
    if (db)
        sqlite3_close(db);
}

void DatabaseManager::createTables() {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "owner TEXT,"
        "balance REAL);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void DatabaseManager::saveAccount(const Account& account) {
    std::string sql =
        "INSERT INTO accounts (owner, balance) VALUES ('" +
        account.getOwner() + "', " +
        std::to_string(account.getBalance()) + ");";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Insert error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}


