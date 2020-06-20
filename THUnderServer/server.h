/*************************************************************************
[Filename]               server.h
[Modules & purpose]      the server class
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include "./socket/Socket.h"
#include "dboperator.h"
#include "User.h"

/*************************************************************************
[Class Name]        Server
[Function]          the server
[Interfaces]        
- constructor Server
- deconstructor ~Server
- accept: accept a socket connection
- Answer: thread function, deal with messages
[Developer & date] 王文新, 2020/6
[Modification log] None
*************************************************************************/
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
