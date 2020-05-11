#pragma once
#include "./socket/Socket.h"
#include <vector>
using std::vector;

class VidServer: public SocketServer {
    friend class TriServer;
private:
    static vector<Socket*> socks;
    
public:
    VidServer(const int port, const int maxnum);
    ~VidServer();
    VidServer(const VidServer&) = delete;
    VidServer& operator = (const VidServer&) = delete;

    static unsigned __stdcall Answer(void* x);
};
