#pragma once
#include "../definitions.h"
#include "../model/stuclient.h"

class Stuop {
private:
    Stuclient* stuclient;

public:
    Stuop(Stuclient*);
    ~Stuop();
    Stuop& operator = (const Stuop&) = delete;
    Stuop(const Stuop&) = delete;

    string receive_msg();
    void send_audiopiece(string&);
    void send_ans(const string&, const unsigned&);
    void send_attention(bool);
};
