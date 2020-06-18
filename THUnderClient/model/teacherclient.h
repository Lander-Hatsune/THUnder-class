#pragma once
#include "client.h"

class Teacherclient: public Client {
public:
    Teacherclient(Client* clt);
    ~Teacherclient();
    void send_audiopiece(string& audio);
    string receive_msg();
    void randcall();
    void endcall();
    void send_prob(string, string, string);
    void pull_prob();
};
