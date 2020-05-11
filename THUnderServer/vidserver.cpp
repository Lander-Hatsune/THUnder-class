#include "vidserver.h"
#include <string>
using std::string;

VidServer::VidServer(const int port, const int maxnum):
    SocketServer(port, maxnum) {
    
}

VidServer::~VidServer() {;}

unsigned __stdcall VidServer::Answer(void* x) {
    Socket* sock = (Socket*) x;
    while (true) {
        string str = sock->ReceiveLine();
        if (str.empty() || str == "\n") break;
        str = str.substr(0, str.length() - 1);
        for (int i = 0; i < VidServer::socks.size(); i++) {
            if (VidServer::socks[i] == sock) continue;
            VidServer::socks[i]->SendLine(str);
        }
    }
}
