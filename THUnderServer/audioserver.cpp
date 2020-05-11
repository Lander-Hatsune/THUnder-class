#include "audioserver.h"
#include <string>
using std::string;

AudioServer::AudioServer(const int port, const int maxnum):
    SocketServer(port, maxnum) {
    
}

AudioServer::~AudioServer() {;}

unsigned __stdcall AudioServer::Answer(void* x) {
    Socket* sock = (Socket*) x;
    while (true) {
        string str = sock->ReceiveLine();
        if (str.empty() || str == "\n") break;
        str = str.substr(0, str.length() - 1);
        for (int i = 0; i < AudioServer::socks.size(); i++) {
            if (AudioServer::socks[i] == sock) continue;
            AudioServer::socks[i]->SendLine(str);
        }
    }
}
