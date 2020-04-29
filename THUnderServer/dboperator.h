/*
The class 'dboperator' for sqlite database operations on server
 */

#pragma once
#include <string>
#include "./sqlite/sqlite3.h"
using std::string;

#define CLTTYPE unsigned
#define ADMIN 1
#define TEACHER 2
#define STU 3

class dboperator {
private:
    sqlite3* db;
public:
    dboperator(const char* path = "./Clients.db");
    ~dboperator();
    dboperator(const dboperator&) = delete;
    dboperator& operator = (const dboperator&) = delete;

    unsigned add_client(const char* username,
                       const char* pswd,
                       const CLTTYPE& type);
    unsigned del_client(const char* username);
    unsigned change_username(const char* username,
                             const char* new_username);
    unsigned change_pswd(const char* username,
                         const char* new_pswd);
    CLTTYPE checktype(const char* username, const char* pswd) const;
    bool exist(const char* username) const;
};
