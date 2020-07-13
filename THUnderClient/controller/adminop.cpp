/*************************************************************************
[Filename]               adminop.cpp
[Modules & purpose]      connect Adminclient & AdminMainPage
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/

#include "adminop.h"

/*************************************************************************
Name:       Adminop
Function:   the construct function
Params:     Adminclient*(input)
Return val: Nan
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Adminop::Adminop(Adminclient* adminclt) {
    this->adminclt = adminclt;
}

/*************************************************************************
Name:       ~Adminop
Function:   the deconstruct function
Params:     None
Return val: Nan
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Adminop::~Adminop() {;}

/*************************************************************************
Name:       add_clientop
Function:   pass the "add" command to client, translate then send the feedback
Params:     string username(input), string pswd(input), unsigned type(input)
Return val: const QString, the feedback of the operation
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
const QString Adminop::add_clientop(const string& username,
                                    const string& pswd,
                                    const CLT_TYPE& type) {
    unsigned ret = this->adminclt->add_client(username, pswd, type);
    switch (ret) {
    case 0:
        return "User added!";
    case 1:
        return "Username already exists!";
    case 2:
        return "Username or password illegal";
    default:
        return "";
    }
}

/*************************************************************************
Name:       del_clientop
Function:   pass the "delete" command to client, translate then send the feedback
Params:     username(input)
Return val: const QString, the feedback
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
const QString Adminop::del_clientop(const string& username) {
    unsigned ret = this->adminclt->del_client(username);
    switch (ret) {
    case 0:
        return "User deleted!";
    case 1:
        return "User not found!";
    default:
        return "";
    }
}

/*************************************************************************
Name:       change_usernameop
Function:   pass the "change username" command to client, translate then send the feedback
Params:     username(input), new_username(input)
Return val: const QString, the feedback
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
const QString Adminop::change_usernameop(const string& username,
                                         const string& new_username) {
    unsigned ret = this->adminclt->change_username(username, new_username);
    switch (ret) {
    case 0:
        return "Username changed!";
    case 1:
        return "User not found!";
    case 2:
        return "New username already exists!";
    case 3:
        return "Username or new username illegal!";
    default:
        return "";
    }
}

/*************************************************************************
Name:       change_pswdop
Function:   pass the "change password" command to client, translate then send the feedback
Params:     username(input), new_pswd(input)
Return val: const QString, the feedback
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
const QString Adminop::change_pswdop(const string& username,
                          const string& new_pswd) {
    unsigned ret = this->adminclt->change_pswd(username, new_pswd);
    switch (ret) {
    case 0:
        return "Password changed!";
    case 1:
        return "User not found!";
    case 2:
        return "Username or new password illegal";
    default:
        return "";
    }
}
