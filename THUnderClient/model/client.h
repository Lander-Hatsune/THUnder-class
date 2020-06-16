#pragma once
#include <string>
#include "Socket.h"
#include "../definitions.h"
using std::string;

class Client {
private:
    string username;
    string pswd;
    CLT_TYPE _type;
    void checktype();

protected:
    SocketClient sock;

public:
    const CLT_TYPE* type;
    Client(const string& username,
           const string& pswd,
           const string& host = HOST,
           const int port = PORT);
    ~Client();
    Client(const Client&);
    Client& operator = (const Client&) = delete;
};
