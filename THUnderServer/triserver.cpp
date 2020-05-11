#include "triserver.h"

TriServer::TriServer(const int txtport, const int audioport,
                     const int vidport, const int maxnum):
    txtserver(txtport, maxnum),
    audioserver(audioport, maxnum),
    vidserver(vidport, maxnum) {
    
}
TriServer::~TriServer() {;}

void TriServer::accept() {
    printf("a new connection\n");
    unsigned ret;
    
    Socket* txtsock = this->txtserver.Accept();
    this->txtserver.socks.push_back(txtsock);
    _beginthreadex(0, 0, txtserver.Answer, (void*) txtsock, 0, &ret);
    
    Socket* audiosock = this->audioserver.Accept();
    this->audioserver.socks.push_back(audiosock);
    _beginthreadex(0, 0, audioserver.Answer, (void*) audiosock, 0, &ret);
    
    Socket* vidsock = this->vidserver.Accept();
    this->vidserver.socks.push_back(vidsock);
    _beginthreadex(0, 0, vidserver.Answer, (void*) vidsock, 0, &ret);
    printf("connection established\n");
    
}
