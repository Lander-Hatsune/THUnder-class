#include "user.h"

User::User(string username, string pswd, unsigned type,
           unsigned number, Socket* sock) {
    this->username = username;
    this->username_w = &this->username;
    this->pswd = pswd;
    this->type = type;
    this->is_online = true;
    this->is_online_w = &is_online;
    this->number = number;
    this->sock = sock;
    this->number_w = &this->number;
}

User::~User() {};

void User::sendmsg(const string& str) {
    this->sock->SendLine(str);
}

void User::offline() {
    this->is_online = false;
}
