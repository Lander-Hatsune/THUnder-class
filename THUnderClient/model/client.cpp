/*************************************************************************
[Filename]               client.cpp
[Modules & purpose]      client base class model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#include "client.h"
using std::string;

/*************************************************************************
Name:       Client
Function:   constructor
Params:     string * 3(input), int(input)
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Client::Client(const string& username, const string& pswd,
               const string& host, const int port):
    sock(host, port) {
    this->username = username;
    this->pswd = pswd;
    this->checktype();
    this->type = &this->_type;
}

/*************************************************************************
Name:       ~Client
Function:   deconstructor
Params:     none
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Client::~Client() {;}

/*************************************************************************
Name:       Client
Function:   copy constructor
Params:     Client&(input)
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Client::Client(const Client& clt):
    sock(clt.sock) {
    this->username = clt.username;
    this->pswd = clt.pswd;
    this->_type = clt._type;
    this->type = &this->_type;
}

/*************************************************************************
Name:       checktype
Function:   use the information to verify identity with server
Params:     void
Return val: void
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
void Client::checktype() {
    sock.SendLine(":CT:" + this->username + ":" + this->pswd);
    string fb = sock.ReceiveLine();
    this->_type = fb[0] - '0';
}
