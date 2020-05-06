#pragma once
#include "../definitions.h"
#include "../view/adminmainpage.h"
#include "../model/client.h"

const string ADD_CLIENT = ":AC:";
const string DEL_CLIENT = ":DC:";
const string CHANGE_USERNAME = ":CU:";
const string CHANGE_PSWD = ":CP:";

class Adminop {
private:
    const Client* clt;
public:
    Adminop(const Client* clt);
    ~Adminop();
    Adminop(const Adminop&) = delete;
    Adminop& Adminop(const Adminop&) = delete;
    void add_client(const string&, const string&) const;
    void del_client(const string&) const;
    void change_username(const string&, const string&) const;
    void change_pswd(const string&, const string&) const;
};

