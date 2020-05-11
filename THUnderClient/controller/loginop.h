#pragma once
#include <string>
#include <QWidget>
#include "../definitions.h"

#include "../model/client.h"
#include "../model/adminclient.h"
#include "../model/teacherclient.h"

#include "../controller/adminop.h"
#include "../controller/teacherop.h"

#include "../view/adminmainpage.h"
#include "../view/teachermainpage.h"
#include "../view/stumainpage.h"

using std::string;

class Loginop {
private:
    unsigned failtime;

public:
    Loginop();
    ~Loginop();
    Loginop(const Loginop&) = delete;
    Loginop& operator = (const Loginop&) = delete;
    
    const QString login(const string&, const string&);
};
