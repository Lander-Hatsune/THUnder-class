#pragma once
#include "client.h"
#include <string>
using std::to_string;

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
