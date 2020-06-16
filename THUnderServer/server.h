#pragma once
#include "./socket/Socket.h"
#include "dboperator.h"
#include "User.h"

class Server: public SocketServer {
public:
    Server(const int port, const int maxnum);
    ~Server();
    Server(const Server&) = delete;
    Server& operator = (const Server&) = delete;
    void accept();
    
    static unsigned __stdcall Answer(void* x);
    static dboperator db;
};
