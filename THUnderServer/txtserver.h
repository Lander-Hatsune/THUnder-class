#pragma once
#include "./socket/Socket.h"
#include "dboperator.h"
#include <vector>
using std::vector;

class TxtServer: public SocketServer {
    friend class TriServer;
public:
    TxtServer(const int port, const int maxnum);
    ~TxtServer();
    TxtServer(const TxtServer&) = delete;
    TxtServer& operator = (const TxtServer&) = delete;
    
    static unsigned __stdcall Answer(void* x);
    
private:
    static dboperator db;
    static std::vector<Socket*> socks;
};
