#pragma once
#include "client.h"

class Stuclient: public Client {
public:
    Stuclient(Client* clt);
    ~Stuclient();
    void send_audiopiece(string&);
    string receive_msg();
    void send_ans(const string&, const unsigned&);
};
