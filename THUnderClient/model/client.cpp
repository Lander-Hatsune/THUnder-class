#include "client.h"
#include <string>
using std::string;

Client::Client(const string& username, const string& pswd,
               const string& host, const int port):
    txtsock(host, port),
    audiosock(host, port + 1),
    vidsock(host, port + 2) {
    this->username = username;
    this->pswd = pswd;
    this->checktype();
    this->type = &this->_type;
}

Client::~Client() {;}

Client::Client(const Client& clt):
    txtsock(clt.txtsock),
    audiosock(clt.audiosock),
    vidsock(clt.vidsock) {
    this->username = clt.username;
    this->pswd = clt.pswd;
    this->_type = clt._type;
    this->type = &this->_type;
}


void Client::checktype() {
    txtsock.SendLine(":CT:" + this->username + ":" + this->pswd);
    string fb = txtsock.ReceiveLine();
    printf("checktype feedback:%s\n", fb.c_str());
    this->_type = fb[0] - '0';
}
