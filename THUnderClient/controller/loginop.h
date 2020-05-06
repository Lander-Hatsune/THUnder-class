#pragma once
#include <string>
#include "../definitions.h"
#include "../model/client.h"
#include "adminop.h"
#include "../view/adminmainpage.h"
using std::string;

class loginop {
private:
    unsigned _failtime;

public:
    const unsigned* failtime;

public:
    loginop();
    ~loginop();
    loginop(const loginop&) = delete;
    loginop& operator = (const loginop&) = delete;
    
    unsigned login(const string&, const string&);
};
