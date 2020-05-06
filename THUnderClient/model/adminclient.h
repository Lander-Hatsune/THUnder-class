#pragma once
#include "client.h"

class Adminclient: public Client {
public:
    Adminclient(const string& host);
};
