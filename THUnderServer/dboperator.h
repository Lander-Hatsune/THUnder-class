/*************************************************************************
[Filename]               dboperator.h
[Modules & purpose]      The class 'dboperator' for sqlite database operations on server
[Developer & date]       ÍõÎÄÐÂ 2020/6
[Modification log]
*************************************************************************/

#pragma once
#include <string>
#include "./sqlite/sqlite3.h"
#include "definitions.h"
using std::string;

const char DBPATH[20] = "./Clients.db";

class dboperator {
private:
    sqlite3* db;
    bool exist(const char* username) const;
public:
    dboperator(const char* path = DBPATH);
    ~dboperator();
    dboperator(const dboperator&);
    dboperator& operator = (const dboperator&);

    unsigned add_client(const char* username,
                       const char* pswd,
                       const unsigned& type);
    unsigned del_client(const char* username);
    unsigned change_username(const char* username,
                             const char* new_username);
    unsigned change_pswd(const char* username,
                         const char* new_pswd);
    unsigned checktype(const char* username, const char* pswd) const;
};
