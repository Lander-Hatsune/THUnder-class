#pragma once
#include "./socket/Socket.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class AudioServer: public SocketServer {
    friend class TriServer;
private:
    static vector<Socket*> socks;
    
public:
    AudioServer(const int port, const int maxnum);
    ~AudioServer();
    AudioServer(const AudioServer&) = delete;
    AudioServer& operator = (const AudioServer&) = delete;

    static unsigned __stdcall Answer(void* x);
};
