/*************************************************************************
[Filename]               client.h
[Modules & purpose]      client base class model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include <string>
#include "Socket.h"
#include "../definitions.h"
using std::string;

/*************************************************************************
[Class Name]        Client
[Function]          the base model of client
[Interfaces]        
- constructor Client
- deconstructor ~Client
- checktype: use the information to verify identity with server
[Developer & date] 王文新, 2020/5
[Modification log] None
*************************************************************************/
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
