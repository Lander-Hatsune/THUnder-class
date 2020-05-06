#include "client.h"
#include <string>
using std::string;

Client::Client(const string& username, const string& pswd,
               const string& host, const int port):
    sock(host, port) {
    this->username = username;
    this->pswd = pswd;
    this->checktype();
    this->type = &this->_type;
}

Client::~Client() {;}

Client::Client(const Client& clt):
    sock(clt.sock) {
    this->username = clt.username;
    this->pswd = clt.pswd;
    this->_type = clt._type;
    this->type = &this->_type;
}


void Client::checktype() {
    sock.SendLine(":CT:" + this->username + ":" + this->pswd);
    string fb = sock.ReceiveLine();
    printf("checktype feedback:%s\n", fb.c_str());
    this->_type = fb[0] - '0';
}
