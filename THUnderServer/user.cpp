/*************************************************************************
[Filename]               user.cpp
[Modules & purpose]      the user class
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#include "user.h"

/*************************************************************************
Name:       User
Function:   the construct function
Params:     string * 2(input), unsigned * 2(input), Socket*(input)
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
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

/*************************************************************************
Name:       ~User
Function:   the deconstruct function
Params:     none
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
User::~User() {};

/*************************************************************************
Name:       sendmsg
Function:   send a message to 'this' user
Params:     string(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void User::sendmsg(const string& str) {
    this->sock->SendLine(str);
}
