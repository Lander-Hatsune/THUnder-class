#pragma once
#include "./socket/Socket.h"
#include <string>
using std::string;

class User {
private:
    string username;
    string pswd;
    unsigned type;
    unsigned number;
    Socket* sock;
    bool is_online;
    
public:
    const string* username_w;
    const unsigned* type_w;
    User(string, string, unsigned, unsigned, Socket*);
    ~User();
    User(User&) = delete;
    User& operator = (User&) = delete;
    void sendmsg(const string& str);
    const unsigned* number_w;
    const bool* is_online_w;
    void offline();
};
