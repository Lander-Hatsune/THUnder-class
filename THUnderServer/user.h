/*************************************************************************
[Filename]               user.h
[Modules & purpose]      the user class
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include "./socket/Socket.h"
#include <string>
using std::string;

/*************************************************************************
[Class Name]        User
[Function]          the user data structure
[Interfaces]        
- constructor User
- deconstructor ~User
- sendmsg: send message to 'this' user
[Developer & date] 王文新, 2020/6
[Modification log] None
*************************************************************************/
class User {
public:
    const string* username_w;
    const unsigned* type_w;
    const unsigned* number_w;

    User(string, string, unsigned, unsigned, Socket*);
    ~User();
    User(User&) = delete;
    User& operator = (User&) = delete;
    void sendmsg(const string& str);
        
private:
    string username;
    string pswd;
    unsigned type;
    unsigned number;
    Socket* sock;
};
