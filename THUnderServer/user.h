#pragma once
#include "./socket/Socket.h"
#include <string>
using std::string;

class User {
public:
    const string* username_w;
    const unsigned* type_w;
    const unsigned* number_w;

    User(string, string, unsigned, unsigned, Socket*);
    ~User();
    User(User&) = delete;
    User& operator = (User&) = delete;
    void sendmsg(const string& str);
        
private:
    string username;
    string pswd;
    unsigned type;
    unsigned number;
    Socket* sock;
};
