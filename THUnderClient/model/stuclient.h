#pragma once
#include "client.h"

class Stuclient: public Client {
    friend class Teacherclient;
public:
    Stuclient(Client* clt);
    ~Stuclient();
    void sendaudio(string&);
    string receiveaudio();
private:
    
};
