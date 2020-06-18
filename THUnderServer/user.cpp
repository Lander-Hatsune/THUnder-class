#include "user.h"

User::User(string username, string pswd, unsigned type,
           unsigned number, Socket* sock) {
    this->username = username;
    this->username_w = &this->username;
    this->pswd = pswd;
    this->type = type;
    this->type_w = &this->type;
    this->number = number;
    this->sock = sock;
    this->number_w = &this->number;
}

User::~User() {};

void User::sendmsg(const string& str) {
    this->sock->SendLine(str);
}
