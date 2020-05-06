#pragma once
#include "client.h"
#include <string>
using std::to_string;

const string ADD_CLIENT = ":AC:";
const string DEL_CLIENT = ":DC:";
const string CHANGE_USERNAME = ":CU:";
const string CHANGE_PSWD = ":CP:";

class Adminclient: public Client {
public:
    Adminclient(Client* clt);
    ~Adminclient();
    Adminclient(const Adminclient&) = delete;
    Adminclient& operator = (const Adminclient&) = delete;

    unsigned add_client(const string&, const string&,
                        const CLT_TYPE& type);
    unsigned del_client(const string&);
    unsigned change_username(const string&, const string&);
    unsigned change_pswd(const string&, const string&);
};
