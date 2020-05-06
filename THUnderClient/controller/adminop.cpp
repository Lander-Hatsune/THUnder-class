#include "adminop.h"

Adminop::Adminop(Adminclient* adminclt) {
    this->adminclt = adminclt;
}

Adminop::~Adminop() {;}

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
