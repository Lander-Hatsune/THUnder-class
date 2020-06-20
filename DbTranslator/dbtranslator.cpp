#include "./sqlite/sqlite3.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(void) {
    sqlite3* db;
    int result = sqlite3_open("./clients.db", &db);
    if (result != SQLITE_OK) {
        printf("Failed to initialize db\n");
    }
    string new_table = "CREATE TABLE ClientInfo (username TEXT [NOT NULL], pswd TEXT[NOT NULL], type INTEGER [NOT NULL])";
    int result2 = sqlite3_exec(db, new_table.c_str(), NULL, NULL, NULL);
    if (result2 != SQLITE_OK) {
        printf("failed to create a new table");
    }

    
    
    freopen("./userinformation.txt", "r", stdin);

    string str;
    int i = 0;
    while (cin >> str) {
        i += 1;
        if (i == 1) {
            cout << str << "items to be translated" << endl;
            continue;
        }

        string username = str;
        string pswd;
        cin >> pswd;
        string type;
        cin >> type;
        if (type == "Admin") {
            type = "1";
        } else if (type == "Teacher") {
            type = "2";
        } else if (type == "Student") {
            type = "3";
        }
        string sql;
        sql = "INSERT INTO ClientInfo VALUES ('" + username + "','"
            + pswd + "','" + type + "')";
        int result = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
        
        if (result == SQLITE_OK) {
            printf("successfully translated\n");
        } else printf("failed to translate\n");
    }
    
    sqlite3_close(db);
    return 0;
}
